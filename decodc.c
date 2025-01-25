#include "decodc.h"

void getBlocos(FILE *arq)
{
  char **vetline;         // Saida da função decodline.
  char line[TAM_LINE];    // Vetor de char, pra leitura do arquivo.
  short int flag_fim = 0; // Fim da MT.
  n_blocos = 0;           // Tamanho do vetor blocos.
  rewind(arq);            // Reinicia ponteiro do arquivo.
  // Faz leitura no aquivo, ate "\n ou \0", ou tamanho passado parâmetro.
  fgets(line, TAM_LINE - 1, arq);
  while (!feof(arq))
  {
    // Trata comentário com, com ";" no incio da linha.
    if (line[0] == ';')
    {
      fgets(line, TAM_LINE - 1, arq);
      continue;
    }
    // Chamada da função quebrando a linha em tokens.
    vetline = decodline(line);
    if (!vetline)
    {
      fgets(line, TAM_LINE - 1, arq);
      continue;
    }
    // Verifica se a linha é uma declaração de um bloco.
    if ((strcmp(vetline[0], "bloco") == 0) && flag_fim)
    {
      fprintf(stderr, "\nERROR SINTAXE BLOCOS, BLOCO '%s'\n\n", blocos[n_blocos - 1].name);
      fclose(arq);
      exit(EXIT_FAILURE);
    }
    if (strcmp(vetline[0], "bloco") == 0)
    {
      // Tratamento de erro sintaxe.
      flag_fim = 1;
      if (cont < 2)
      {
        fprintf(stderr, "\nERROR SINTAXE BLOCOS\n\n");
        fclose(arq);
        exit(EXIT_FAILURE);
      }
      else
      {
        if (cont < 3)
        {
          fprintf(stderr, "\nERROR SINTAXE BLOCOS, BLOCO '%s'\n\n", vetline[1]);
          fclose(arq);
          exit(EXIT_FAILURE);
        }
      }
      // Criando o vetor, e expandindo o seu tamanho a cada novo bloco.
      if (n_blocos == 0)
        blocos = (bloco *)malloc(sizeof(bloco) * (++n_blocos));
      else
        blocos = (bloco *)realloc(blocos, sizeof(bloco) * (++n_blocos));
      // Setando o bloco no vetor blocos.
      strcpy(blocos[n_blocos - 1].name, vetline[1]);
      blocos[n_blocos - 1].position_file = ftell(arq); // posição no arquivo.
      strcpy(blocos[n_blocos - 1].initState, vetline[2]);
    }
    if (strcmp(vetline[0], "fim") == 0)
      flag_fim = 0;
    // Refaz a leitura para o loop.
    fgets(line, TAM_LINE - 1, arq);
  }
  if (flag_fim)
  {
    fprintf(stderr, "\nERROR SINTAXE BLOCOS, BLOCO '%s'\n\n", blocos[n_blocos - 1].name);
    fclose(arq);
    exit(EXIT_FAILURE);
  }
}

char **decodline(char *line)
{
  char **vetoken = NULL; // Vetor de string de saída.
  char *token = NULL;    // String usada para strtok.
  cont = 0;              // Tamanho do Vetor de string (vetoken).

  token = strtok(line, ";\n");  // Trata comentário no meio da linha.
  token = strtok(token, " \t"); // Quebra em tabulação e/ou espaço dos tokens.

  while (token)
  {
    // Aloca e expande o tamanho do vetor para saída.
    if (!vetoken)
      vetoken = (char **)malloc((++cont) * sizeof(char *));
    else
      vetoken = (char **)realloc(vetoken, (++cont) * sizeof(char *));
    // Setando o token no vetor.
    vetoken[cont - 1] = token;
    // Pega proximo token.
    token = strtok(NULL, " \t");
  }
  return vetoken;
}
