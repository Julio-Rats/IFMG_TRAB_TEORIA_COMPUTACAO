#include "decodArgs.h"

void decodArgs(int argc, char *argv[])
{
    modo = type_r; // Modo setado em modo padr�o .
    n_step = 1;    // Numero padr�o par�metro -s.
    step_arg = 1;  // Numero padr�o par�metro -s.

    strncpy(delim_cabecote, DELIM_PADRAO, 2); // Setando os delimitadores do cabe�ote padr�o "( )".

    if (argc == 2)
        return;

    for (size_t i = 1; i < argc; i++)
        // Pega os PAR�METROS.
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
                    // Pegando e tratando par�metro -s
                    n_step = atol(argv[i + 1]) + 1;
                    step_arg = n_step;
                    if (n_step == 0)
                    {
                        fprintf(stderr, "\nERROR PAR�METRO '-S' VALOR \"N\" N�O INFORMADO OU IGUAL A ZERO\n\n");
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
                // Par�metro invalido.
                fprintf(stderr, "\nERROR SINTAXE PAR�METRO %s INVALIDO\n\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
}
