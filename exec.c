#include "exec.h"

static size_t n_exec = 0;

/*
  Função onde procura pelo nome do bloco, e seta as variáveis de controle da
    MT, de acordo com as variáveis do bloco a ser executado.
        variáveis de um bloco:
                name          : Nome do bloco.
                initState     : Numero do estado inicial do bloco.
                position_file : Posição no arquivo onde inicia o bloco.
                ================> variáveis de controle da MT <==============
                name_bloco    : Nome do bloco a ser executado.
                estado_atual  : Estado atual na MT.
                seek          : Posição do arquivo para busca de blocos.
                n_bloco       : Numero de blocos salvos no vetor (length).
*/
void setseekbloco(FILE *arq, char *name_bloco)
{
    memmove(bloco_atual, name_bloco, strlen(name_bloco) + 1);
    for (size_t i = 0; i < n_blocos; i++)
        if (strcmp(blocos[i].name, name_bloco) == 0)
        {
            strcpy(estado_atual, blocos[i].initState);
            seek = blocos[i].position_file;
            return;
        }
    fprintf(stderr, "\nERRO BLOCO '%s' NÃO ENCONTRADO\n", name_bloco);
    para(arq);
}

void exec(FILE *arq)
{
    n_exec = 0;                                           // Contador de números de execução.
    pilha_blocos = initStack();                           // Pilha para chamadas de blocos.
    cabecote = 0;                                         // Reset posição do cabeçote sobre a fita.
    char **vetoken = NULL;                                // Vetor com as tokens das linhas de instrução.
    char *line = (char *)malloc(sizeof(char) * TAM_LINE); // "String" leitura do aquivo.
    char type_cod;                                        // Tipo de instrução a ser executada, 0 = instrução normal, 1 = instrução chamada bloco.

    setseekbloco(arq, "main");  // Seta variáveis de controle do bloco main.
    fseek(arq, seek, SEEK_SET); //  Aplica posição inicio do bloco main.

    fgets(line, TAM_LINE - 1, arq); // Leitura de uma linha do arq.
    while (!feof(arq))
    {
        if (NO_LOOP)
            if (n_exec >= LIMIT_LOOP) // Verifica quant de interações, tratar loops.
            {
                if (modo != type_s)
                {
                    print(0, arq); // Chama função para imprimir
                    modo = type_v; // Seta para imprimir.
                }                  // Verifica se esta no modo de não impressão.
                fprintf(stderr, "\nMT PARADA, POSSIVEL LOOP INFINITO\n\n");
                para(arq);
            }
        if (line[0] == ';') // Verifica linha de comentário.
        {
            fgets(line, TAM_LINE - 1, arq);
            continue;
        }

        vetoken = decodline(line); // Decodifica linha e retorna tokens

        if (!vetoken) // Verifica se a linha foi de comentário.
        {
            fgets(line, TAM_LINE - 1, arq);
            continue;
        }

        if (strcmp(vetoken[0], "fim") == 0) // Verifica se não existe transição definida.
        {
            strtok(estado_atual, "\n"); //  Remove \n para apresentação no printf.
            modo = type_v;              //   Muda modo para que acha sempre essa impressão.
            print(0, arq);              //    Printa essa ultima execução.
            // ----- MANDA MSG COM ERRO PARA O USUÁRIO ----- //
            fprintf(stderr, "\nERROR TRANSIÇÃO BLOCO '%s' ESTADO '%s' COM '%c' NÃO DEFINIDA\n\n", bloco_atual, estado_atual, fita[cabecote]);
            fprintf(stderr, "ESTADO '%s' NÃO EXISTE ", estado_atual);
            fprintf(stderr, "OU SIMBOLO '%C' NÃO DEFINIDO NO ALFABETO\n", fita[cabecote]);
            para(arq); // Finaliza MT.
        }

        if (atoi(vetoken[0]) == atoi(estado_atual)) // Verifica se esta numa transição desse estado.
        {
            if (cont < 3) // Verifica erro de SINTAXE.
            {
                fprintf(stderr, "ERRO SINTAXE BLOCO '%s' ESTADO '%s'\n\n",
                        bloco_atual, estado_atual);
                fclose(arq);
                exit(EXIT_FAILURE);
            }
            if (strcmp(vetoken[2], "--") == 0) // Define o tipo da instrução.
                type_cod = 0;                  // Instrução normal.
            else
                type_cod = 1; // Instrução

            simbolo_atual[0] = fita[cabecote]; // Seta simbolo atual da fita.
            simbolo_atual[1] = '\0';
            if ((type_cod == 0) && ((strcmp(simbolo_atual, vetoken[1]) == 0) ||
                                    (strcmp(vetoken[1], "*") == 0)))
            { // Verifica se pertence a esta transição.

                n_exec++;                // Incrementa num de execução feitas.
                execinstr(vetoken, arq); // Executa linha de instruções normais.
            }
            else if (type_cod == 1)
                execblock(vetoken, arq); // Executa linha de instruções de blocos.
        }

        if (vetoken) // Desaloca Tokens.
        {
            free(vetoken);
            vetoken = NULL;
        }
        fgets(line, TAM_LINE - 1, arq); // Leitura da proxima linha e loop.
    }
}
/*
    Para execução da MT.
*/
void para(FILE *arq)
{
    printf("\nMT ENCERROU:  %ld execuções efetuadas\n\n", n_exec);
    fclose(arq);
    exit(EXIT_SUCCESS);
}
/*
      Executa transição 'setando' as variáveis de controle
        da MT, printa se estiver no modo correto, e volta para
        inicio do bloco no aquivo para busca de nova transição
        com novo estado e simbolo.
*/
void execinstr(char **vetline, FILE *arq)
{

    char fin = 0; // Define se Fim de execução; 1==fim.
    // Verifica erro de SINTAXE.
    if (cont < 6)
    {
        fprintf(stderr, "ERRO SINTAXE BLOCO '%s' ESTADO '%s'\n\n",
                bloco_atual, estado_atual);
        fclose(arq);
        exit(EXIT_FAILURE);
    }
    // simbolo_novo
    if (strcmp(vetline[3], "*") != 0)
        fita[cabecote] = vetline[3][0];

    
    // movimento cabeçote
    if (strcmp(vetline[4], "e") == 0)
    {
        // Tratamento se o cabecote ir além do inicio da fila, índice -1 em C.
        if (cabecote == 0)
        {
            for (int i = (strlen(fita) - 2); i >= 0; i--)
                fita[i + 1] = fita[i];

            fita[0] = '_';
            cabecote = 0;
        }
        else
        {
            cabecote--;
        }
    }else if (strcmp(vetline[4], "d") == 0)
        cabecote++;

    // Verifica erro de SINTAXE.
    else if (strcmp(vetline[4], "i") != 0)
    {
        fprintf(stderr, "\nERRO SINTAXE MOVIMENTO BLOCO '%s' ESTADO '%s' COM SIMBOLO '%s'\n\n",
                bloco_atual, estado_atual, estado_atual);
        fclose(arq);
        exit(EXIT_FAILURE);
    }
    
    // Estado novo
    if (strcmp(vetline[5], "pare") == 0) // Verifica Fim do algorítimo.
        fin = 1;
    else if (strcmp(vetline[5], "retorne") == 0) // Verifica retorno de um bloco.
    {
        do
        {
            recall *retorno = popStack(pilha_blocos); // Desempilha bloco da pilha.
            if (!retorno)                             // Trata algum erro se ocorrer.
            {
                printf("\nERRO DE RETORNO DO BLOCO '%s' \n", bloco_atual);
                para(arq);
            }
            /* Seta variáveis de controle:
                bloco_atual : Nome do bloco atual.
                n_bloco_atual : Posição no vetor (índice).
                novo_estado   : Novo Estado da MT, estado de retorno.
                estado_atual  : Estado atual da MT.
            */
            strcpy(bloco_atual, (char *)retorno->recall_bloco);
            strcpy(novo_estado, retorno->recall_state);
            strcpy(estado_atual, novo_estado);
            // Verifica se a retornada é um pare.
            if (strcmp(novo_estado, "pare") == 0)
            {
                fin = 1;
                strcpy(novo_estado, (char *)retorno->final_state);
                strcpy(estado_atual, novo_estado);
            }
        } while (strcmp(novo_estado, "retorne") == 0);
    }
    else
    {
        // Caso não seja um retorno seta o novo estado.
        if (strcmp(vetline[5], "*") == 0)
            strcpy(novo_estado, estado_atual);
        else
            strcpy(novo_estado, vetline[5]);
    }
    // Tratar o comando "!".
    if (cont > 6)
        if (strcmp("!", vetline[6]) == 0)
            modo = type_v;
    /*
      Imprime a execução e seta o inicio do bloco no arq para
          nova busca de transição para novo estado e simbolo.
    */
    print(fin, arq);
    setseekbloco(arq, bloco_atual);
    strcpy(estado_atual, novo_estado);
    fseek(arq, seek, SEEK_SET);
}
/*
    Executa instrução de chamada de blocos, empilha o bloco atual.
*/
void execblock(char **vetline, FILE *arq)
{
    print(0, arq); // Imprime execução atual.
    recall *retorno = NULL;
    retorno = (recall *)malloc(sizeof(recall)); // Aloca ED de chamada de bloco.
    if (!retorno)                               // Trata possível erro de alocação.
    {
        fprintf(stderr, "\nERRO ALOCAÇÃO DE CHAMADA DE BLOCO\n\n");
        exit(EXIT_FAILURE);
    }

    strcpy((char *)retorno->recall_bloco, bloco_atual); // Seta na strtc nome do Bloco atual.
    if (strcmp(vetline[2], "pare") == 0)
        strcpy(retorno->final_state, estado_atual); // Seta na strtc estado de retorno.

    strcpy(retorno->recall_state, vetline[2]); //    Seta na strtc estado de retorno.
    pushStack(pilha_blocos, retorno);          //    Empilha esse bloco na ED pilha.
    setseekbloco(arq, vetline[1]);             //    Seta variáveis de controle.
    print(0, arq);                             //    Imprime execução.
    fseek(arq, seek, SEEK_SET);                //    Seta posição no arq com novo bloco.

    if (cont > 3) // Trata operador "!"
        if (strcmp("!", vetline[3]) == 0)
            modo = type_v;
}

/*
  Imprime conforme requisitado no documento do trabalho.
*/
void print(int fin, FILE *arq)
{
    int return_scanf;
    int dots;
    int fitantes, fitapos;
    char flagvaziantes = 1;
    char fitaprint[LEN_FITA_PRINT + 6];
    char ponts[TAM_BLOCK];

    if (modo != type_r) // Modo de impressão.
    {
        dots = TAM_BLOCK - strlen(bloco_atual) - 1;                      // Sobra do nome do bloco, a ser preenchido de pontos.
        fitapos = cabecote + (int)((LEN_FITA_PRINT) / 2) - strlen(fita); // Excesso ou falta de símbolos depois do cabeçote.
        fitantes = (int)((LEN_FITA_PRINT) / 2) - cabecote;               // Excesso ou falta de símbolos antes do cabeçote.
        // Verifica se houve excesso antes.
        if (fitantes < 0)
        {
            fitantes *= -1;    // "ABS"
            flagvaziantes = 0; // Desativa FLAG;
        }
        // Verifica se houve excesso apos.
        if (fitapos < 0)
            fitapos *= -1;
        int cont = 0;
        // Cria a "LINHA" de impressão.
        if (flagvaziantes) // Trata se tiver menos de 20 antes do cabecote.
        {
            strcpy(fitaprint, "");
            for (int i = 0; i < fitantes; i++)
                strcat(fitaprint, "_");
            cont = fitantes;
            strncat(fitaprint, fita, cabecote);
            cont += cabecote;
        }
        else
        { // Trata se tiver mais de 20 antes do cabecote.
            strcpy(fitaprint, "");
            for (int i = fitantes; i < cabecote; i++)
                fitaprint[cont++] = fita[i];
            fitaprint[cont] = '\0';
        }

        char pont[6];
        // Cria "visual" do cabeçote.
        pont[0] = (char)delim_cabecote[0];
        pont[1] = ' ';
        pont[2] = (char)fita[cabecote];
        pont[3] = ' ';
        pont[4] = (char)delim_cabecote[1];
        pont[5] = '\0';
        cont += 5;

        // Adiciona cabecote na impressão.
        strcat(fitaprint, pont);
        // Adiciona a frente do cabecote na impressão.
        for (int i = cabecote + 1; i < cabecote + (int)((LEN_FITA_PRINT) / 2) + 1; i++)
            fitaprint[cont++] = fita[i];
        fitaprint[LEN_FITA_PRINT + 6 - 1] = '\0';
        // ADD pontos ante do nome do bloco
        memset(ponts, '.', dots);
        ponts[dots] = '\0';
        // Imprimi.
        printf("%s%s.%04d:%s\n", ponts, bloco_atual, atoi(estado_atual), fitaprint);
        // Trata modo -s, quando o valor inspirar.
        if ((n_step <= n_exec) && (modo == type_s))
        {
            char op[3];
            long int n_temp = -1;
            printf("\nForneça opção '-r', '-v', '-s numero' ou 'qualquer outro para continuar': ");
            return_scanf = scanf("%s", op);
            // Pega a nova op de modo, se for -s ou -n trata possíveis erros.
            if (strlen(op) > 1)
                switch (op[1])
                {
                case 'r':
                    modo = type_r;
                    break;
                case 'v':
                    modo = type_v;
                    break;
                case 's':
                    do
                    {
                        printf("Digite o numeros de passos: ");
                        return_scanf = scanf("%ld", &n_temp);
                    } while (return_scanf == EOF);
                    while (n_temp <= 0)
                        do
                        {
                            printf("Digite um numero maior que zero: ");
                            return_scanf = scanf("%ld", &n_temp);
                        } while (return_scanf == EOF);
                    n_step = n_exec + n_temp;
                    step_arg = n_temp;
                    break;
                case 'n':
                    n_step += step_arg;
                    break;
                default:
                    n_step += step_arg;
                    break;
                }
            else
                n_step += step_arg;
            printf("\n");
        }
    }
    // Caso o modo encontre um pare , ele entrara aq e finalizara a MT.
    if (fin)
    {
        if (modo == type_r)
        {
            modo = type_v;
            print(1, arq);
        }
        para(arq);
    }
}
