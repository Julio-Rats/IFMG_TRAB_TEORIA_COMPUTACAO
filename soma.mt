;
;
;   Efetua a soma de dois números binários de mesmo tamanho
;   ambos separados por '#'
;
;   Exemplo: 010#101
;

bloco main 28
    ; Verifica simbolo separador
    28 # -- * i 29
    28 _ -- * e 21
    28 * -- * d 28
    29 _ -- * d 1
    29 * -- * e 29

    ; Adiciona simbolo no inicio e no fim, junto com bit de care
    1 _ -- $ d 2
    1 * -- * e 1

    2 _ -- % d 3
    2 * -- * d 2

    3 * -- 0 i 4

    4 goto_esq_centro 5
    6 goto_dir_centro 5

    ; pega o primeiro simbolo
    5 0 -- X i 8
    5 1 -- X i 9
    5 $ -- * i 25
    5 * -- * e 5

    ; pega o segundo considerando zero no primeiro
    8 goto_dir_final 10
    10 0 -- Y i 12
    10 1 -- Y i 13
    10 # -- * i 21
    10 * -- * e 10

    ; pega o segundo considerando um no primeiro
    9 goto_dir_final 11
    11 0 -- Y i 13
    11 1 -- Y i 14
    11 # -- * i 21
    11 * -- * e 11

    ; 0x0
    12 goto_care 15
    15 1 -- 0 i 19
    15 0 -- * i 18

    ; 0x1 or 1x0
    13 goto_care 16
    16 1 -- * i 18
    16 0 -- * i 19

    ; 1x1
    14 goto_care 17
    17 1 -- * i 19
    17 0 -- 1 i 18

    ; Verifica se existe simbolos na segunda (desigualdade)
    25 goto_dir_centro 26
    26 * -- * d 27
    27 Y -- * i 20
    27 * -- * i 21

    ; verifica o ultimo care
    20 goto_care 22
    22 0 -- * i 23
    22 1 -- 0 i 24
    24 write_one 23


    18 write_zero 6
    19 write_one 6

    23 aceita pare
    21 error  pare
fim

bloco goto_dir_centro 1
    1 # -- * i retorne
    1 * -- * d 1
fim

bloco goto_esq_centro 1
    1 # -- * i retorne
    1 * -- * e 1
fim

bloco goto_dir_final 1
    1 % -- * i retorne
    1 * -- * d 1
fim

bloco write_zero 1
    1 _ -- 0 i retorne
    1 * -- * e 1
fim

bloco write_one 1
    1 _ -- 1 i retorne
    1 * -- * e 1
fim

bloco goto_care 1
    1 % -- * d retorne
    1 * -- * d 1
fim

bloco error 1
	1 apaga_fita 3
	3 * -- N d 4
	4 * -- A d 5
	5 * -- O d 6
	6 * -- _ d 7
	7 write_aceita 8
  8 * -- * i retorne
fim

bloco aceita 1
   1 _ -- * i 2
	 1 * -- * d 1
   2 $ -- _ e 3
   2 * -- _ e 2
   3 _ -- * i 4
   3 * -- * e 3
   4 write_result 5
   5 * -- * i retorne
fim

bloco apaga_fita 1
	1 _ -- * e 2
	1 * -- * d *
	2 _ -- * d retorne
	2 * -- _ e *
fim

bloco write_aceita 1
	1 * -- A d 2
	2 * -- C d 3
	3 * -- E d 4
	4 * -- I d 5
	5 * -- T d 6
	6 * -- A d retorne
fim

bloco write_result 1
    1 * -- : e 2
    2 * -- t e 3
    3 * -- l e 4
    4 * -- u e 5
    5 * -- s e 6
    6 * -- e e 7
    7 * -- R i retorne
fim
