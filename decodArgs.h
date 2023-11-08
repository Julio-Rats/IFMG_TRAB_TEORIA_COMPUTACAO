#ifndef DECODARGS
#define DECODARGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DELIM_PADRAO "()\0"
/*
    Enum para definir qual PAR?METRO de impress�o a MT executara.
*/

typedef enum
{
    type_r, //  Tipo silencioso
    type_v, //  Tipo "verboso"
    type_s  //  Tipo n step para e pega novo modo
} type_mod;

type_mod modo; // Vari�vel GLOBAL de controle de PAR�METRO

size_t n_step;          // vari�vel de controle para entrada do tipo -S (numero de passos)
size_t step_arg;        // vari�vel de controle para novas entradas do tipo -s
char delim_cabecote[3]; // Delimitador do cabe�ote entrada -h

// L� os par�metros e decodifica.

void decodArgs(int argc, char *argv[]);

#endif
