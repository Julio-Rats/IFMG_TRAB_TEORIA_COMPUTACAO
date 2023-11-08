#include "main.h"
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    if (argc < 2)
        erroArgs(argv[0]);

    FILE *file;
    if (!(file = fopen(argv[argc - 1], "r")))
    {
        fprintf(stderr, "\nERROR AO TENTAR ABRIR O ARQUIVO %s\n\n", argv[argc - 1]);
        exit(EXIT_FAILURE);
    }

    decodArgs(argc, argv);
    getBlocos(file);

    memset(fita, '_', TAM_FITA - 1);
    interface();
    exec(file);

    return 0;
}

#ifdef _WIN32
    #define CLEAR "cls"
#elif __linux__
    #define CLEAR "clear"
#else
    #error "OS Not Supported"
#endif

void interface()
{
    char input[TAM_INPUT];
    system(CLEAR);
    printf("Simulador de M�quina de Turing ver. 1.1\nDesenvolvido como trabalho pr�tico para ");
    printf("a disciplina de Teoria da Computa��o\n");
    printf("Autor: J�lio C�sar M. C�ndido - IFMG 2018 Campus Formiga.\n\nForne�a a palavra inicial: ");
    scanf("%s", input);
    printf("\n");
    strncpy(fita, input, strlen(input));
}

void erroArgs(char *exec_name)
{
    system(CLEAR);
    printf("Error: Falta de par�metro, exemplo:\n\n\t%s [Op��es] [-head xx] <Fonte(MT)>\n\n", exec_name);
    printf("Op��es:\n\t< -r > Modo execu��o silenciosa (Padr�o)\n\t");
    printf(" -v Modo debug, passo a passo\n\t");
    printf(" -s n Executa n computa��es e espera uma novo modo de entrada\n\t");
    printf(" -head xx Marcadores do cabe�ote na impress�o da fita\n\n");
    printf(" Fonte(MT) Entrada com arquivo.MT com c�digo de execu��o\n\n");
    exit(1);
}
