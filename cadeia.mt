;
; Expressão definida por a^(N)b^(2N)c^(3N)
;
bloco main 0
	0 _ -- * i 11
	0 * -- * i 1

	1 a -- X d 2
	1 Y -- * i 9
	1 * -- * i 10

	2 a -- * d *
	2 Y -- * d *
	2 b -- Y d 3
	2 * -- * i 10

	3 b -- Y d 4
	3 * -- * i 10

	4 b -- * d *
	4 Z -- * d *
	4 c -- Z d 5
	4 * -- * i 10

	5 c -- Z d 6
	5 * -- * i 10
	6 c -- Z d 7
	6 * -- * i 10

	7 X -- * d 1
	7 * -- * e *

	9 verifica pare

	11 aceita pare
	10 error pare

fim

bloco verifica 1
	1 _ -- * d 2
	1 * -- * e *

	2 a -- * d 3
	2 b -- * d 3
	2 c -- * d 3
	2 _ -- * i 4
	2 * -- * d *

	3 error 5
	4 aceita 5

	5 * -- * i retorne

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
	1 apaga_fita 3
	3 * -- S d 4
	4 * -- I d 5
	5 * -- M d 6
	6 * -- _ d 7
	7 write_aceita 8
	8 * -- * i retorne
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
