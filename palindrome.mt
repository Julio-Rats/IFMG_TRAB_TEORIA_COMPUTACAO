;
;	Verifica se a sequencia de 0 e 1, é uma palindrome
;	 respondendo sim ou não.
;
bloco main 01

	01 0 -- A i 10
	01 1 -- B i 20
	10 moveFim 11
	20 moveFim 21
	   ;    leu 0
	11 iniEsq 12
	12 0 -- A i 30
	12 1 -- * i 70
	12 _ -- * d 60

	; leu 1
	21 iniEsq 22
  22 0 -- * i 70
	22 1 -- B i 30
	22 _ -- * d 60

	30 moveIni 31
	31 iniDir 32
	32 _ -- * e 60
	32 * -- * i 01

	60 sim pare
	70 nao pare

fim ; main

; move para ultimo caractere da palavra
bloco moveFim 01
	01 _ -- * e retorne
	01 * -- * d *
fim ; moveFim

; move para primeiro caractere da palavra
bloco moveIni 01
	01 _ -- * d retorne
	01 * -- * e *
fim ; moveIni

; recua ate caracetere minusculo ou _
bloco iniEsq 01
	01 _ -- * i retorne
	01 0 -- * i retorne
	01 1 -- * i retorne
	01 * -- * e *
fim ; iniEsq

; avanca ate caractere minusculu ou _
bloco iniDir 01
	01 _ -- * i retorne
	01 0 -- * i retorne
	01 1 -- * i retorne
	01 * -- * d *
fim ; iniDir

; Apaga tudo
bloco ApagaTudo 01
	01 _ -- * d retorne
	01 * -- _ e 01
fim ; apaga tudo

; palavra eh palindromo
bloco sim 01
	01 moveFim 02
	02 ApagaTudo 03
	03 * -- * d 04
	04 * -- _ d 05
	05 * -- S d 06
	06 * -- I d 07
	07 * -- M d retorne
fim ; sim

; palavra nao eh palindromo
bloco nao 01
	01 moveFim 02
	02 ApagaTudo 03
	03 * -- * d 04
	04 * -- _ d 05
	05 * -- N d 06
	06 * -- A d 07
	07 * -- O d retorne
fim ; nao
teste
