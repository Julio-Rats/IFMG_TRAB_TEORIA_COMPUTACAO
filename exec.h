#ifndef EXEC
#define EXEC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodc.h"
#include "decodArgs.h"
#include "stack.h"

#define NO_LOOP 0          // 1-True, 0-False
#define LIMIT_LOOP 1000000 // Max iteration for loop detection
#define LEN_FITA_PRINT 40  // Tamanho da fita na impressão

typedef unsigned long long ullong;

stack *pilha_blocos;          //  Pilha para chamada de blocos.
char estado_atual[TAM_STATE]; //  Estado atual da maquina
char novo_estado[TAM_STATE];  //  Estado atual e proximo a ser carrego.
char bloco_atual[TAM_BLOCK];  //  Bloco atual de execução da MT.
char simbolo_atual[2];        //  Simbolo atual sobre o cabeçote.
char fita[TAM_FITA];          //  Fita da MT.
ullong cabecote;              //  Posição do cabeçote na fita da MT.
size_t seek;                  //  Semente para andar no arquivo.

void execinstr(char **vetline, FILE *arq); // Executa instrução do tipo manipulador de símbolos
void execblock(char **vetline, FILE *arq); // Executa instrução do tipo chamada de blocos
void print(int fin, FILE *arq);            // Printa Status(FITA) na tela.
void exec(FILE *arq);                      // Executa todo o algorítimo(arquivo) da MT.
void para(FILE *arq);                      // Finaliza a MT.

#endif
