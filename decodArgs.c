#include "decodArgs.h"

void decodArgs(int argc, char *argv[])
{
    modo = type_r; // Modo setado em modo padrão .
    n_step = 1;    // Numero padrão parâmetro -s.
    step_arg = 1;  // Numero padrão parâmetro -s.

    strncpy(delim_cabecote, DELIM_PADRAO, 2); // Setando os delimitadores do cabeçote padrão "( )".

    if (argc == 2)
        return;

    for (size_t i = 1; i < argc; i++)
        // Pega os PARÂMETROS.
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i], "-r") == 0)
                // modo   = type_r; // Tipo -r
                continue;
            else if (strcmp(argv[i], "-v") == 0)
                modo = type_v; // Tipo -v
            else if (strcmp(argv[i], "-s") == 0)
            {
                modo = type_s; // Tipo -s
                if (argc >= (i + 1))
                {
                    // Pegando e tratando parâmetro -s
                    n_step = atol(argv[i + 1]) + 1;
                    step_arg = n_step;
                    if (n_step == 0)
                    {
                        fprintf(stderr, "\nERROR PARÂMETRO '-S' VALOR \"N\" NÃO INFORMADO OU IGUAL A ZERO\n\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            else if (strcmp(argv[i], "-head") == 0)
            {
                delim_cabecote[0] = argv[i + 1][0];
                delim_cabecote[1] = argv[i + 1][strlen(argv[i + 1]) - 1];
                delim_cabecote[2] = '\0';
            }
            else
            {
                // Parâmetro invalido.
                fprintf(stderr, "\nERROR SINTAXE PARÂMETRO %s INVALIDO\n\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
}
