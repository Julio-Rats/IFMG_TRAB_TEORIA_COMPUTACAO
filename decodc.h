#ifndef  DECODC
#define  DECODC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define   TAM_FITA  1048576 // Tamanho da fita da MT.
#define   TAM_LINE  256     // Tamanho de leitura no aquivo.
#define   TAM_BLOCK 17
#define   TAM_STATE 5
/*
  bloco : Estrutura com nome do bloco, o estado inicial,
          e a inicio do bloco no arquivo.
*/

typedef struct
{
    u_int8_t  name[TAM_BLOCK];      // Nome do bloco declarado.
    u_int8_t  initState[TAM_STATE]; // Estado inicial do bloco.
    u_int32_t position_file;         // posição do bloco no arquivo.
}bloco;

/*
  blocos:   Nome dado ao vetor com todos os blocos encontrados no arquivo.
  n_blocos: Indicador do tamanho do vetor blocos, com struct bloco.
  cont:     Indicador do tamanho do vetor de saida da função decodline.
*/

bloco*    blocos;
u_int16_t n_blocos;
u_int16_t cont;

/* Função getBlocos: pega todos os blocos no arquivo, salvando em uma lista
      com nome, posição no arquivo e estado inicial do bloco de intstrução.

   Função decodline: pega uma linha como entrada e quebra em
          tokens e retorna um vetor de strings com os tonkes.
*/

u_int8_t** decodline(u_int8_t* line);
void       getBlocos(FILE *arq);

#endif
