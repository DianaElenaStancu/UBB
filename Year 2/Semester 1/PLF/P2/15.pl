/*
sa se determine cea mai lunga secventa de numere pare consecutive dintr-o lista (daca sunt mai multe secvente de lungime maxima, una dintre ele).
*/

concat([], C, C).
concat([H|T], C, [H|R]):-
	concat(T, C, R).

 
/*
predicat care determina toate secventele dintr-o lista
*/

secv([], []).
secv([_|T], R):-
	R = [],
	secv(T, R).
secv([H|T], [H|R]):-
	secv(T, R).

toate_secv([], []).
toate_secv([H|T], R):-
	findall(S,secv([H|T], S), R1),
	toate_secv(T, R2),
	concat(R1, R2, R).

/*
secv_par
*/
secv_par([], []).
secv_par([H|T], R):- 
	1 is mod(H,2),
	R = [], 
	secv_par(T, R).
secv_par([H|T], [H|R]):-
	0 is mod(H, 2),
	secv_par(T, R).


/*
lung(l1...ln) = 	0, n = 0
			lung(l2..ln) + 1, n > 0
*/
lung([], 0).
lung([H|T], C):-
	lung(T, C1),
	C is C1 + 1.

/*
verpar(l1...ln) = 	true, n = 0
			verpar(l2...ln), l1 % 2 == 0
			false
*/

verpar([]).
verpar([H|T]):-
	0 is mod(H, 2),
	verpar(T).

alege_par([], []).
alege_par([H|T], R):-
	alege_par(T, R1),
	

/*
alege(l1...ln) = 	[], n = 0
			l1, verpar(l1) = true, lung(l1) > alege		
*/
alege(L, R):-
	toate_secv(L, S),
	alege_par(S, R).

