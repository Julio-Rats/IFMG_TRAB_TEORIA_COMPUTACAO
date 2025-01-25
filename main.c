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
#elif __linux__ || (__APPLE__ && __MACH__)
    #define CLEAR "clear"
#else
    #error "OS Not Supported"
#endif

void interface()
{
    char input[TAM_INPUT];
    system(CLEAR);
    printf("Simulador de MÃ¡quina de Turing ver. 1.1\nDesenvolvido como trabalho prÃ¡tico para ");
    printf("a disciplina de Teoria da ComputaÃ§Ã£o\n");
    printf("Autor: JÃºlio CÃ©sar M. CÃ¢ndido - IFMG 2018 Campus Formiga.\n\nForneÃ§a a palavra inicial: ");
    scanf("%s", input);
    printf("\n");
    strncpy(fita, input, strlen(input));
}

void erroArgs(char *exec_name)
{
    system(CLEAR);
    printf("Error: Falta de parÃ¢metro, exemplo:\n\n\t%s [OpÃ§Ãµes] [-head xx] <Fonte(MT)>\n\n", exec_name);
    printf("OpÃ§Ãµes:\n\t< -r > Modo execuÃ§Ã£o silenciosa (PadrÃ£o)\n\t");
    printf(" -v Modo debug, passo a passo\n\t");
    printf(" -s n Executa n computaÃ§Ãµes e espera uma novo modo de entrada\n\t");
    printf(" -head xx Marcadores do cabeÃ§ote na impressÃ£o da fita\n\n");
    printf(" Fonte(MT) Entrada com arquivo.MT com cÃ³digo de execuÃ§Ã£o\n\n");
    exit(1);
}
