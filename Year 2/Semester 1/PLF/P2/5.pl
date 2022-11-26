/*
afisati pozitiile elementului maxim dintr-o lista
*/
/*
cauta_max(l1...ln) = 	l1, n = 0
			l1, l1 > cauta_max(l2...ln)
			cauta_max(l2...ln), altfel
*/
cauta_max([H], H):- !.
cauta_max([H|T], R):-
	cauta_max(T, R1),
	H > R1, !, 
	R = H.
cauta_max([_|T], R):-
	cauta_max(T, R1),
	R = R1.
/*
poz(l1..ln, e, c) = 	c (+) poz(l2...ln, e, c + 1), l1 = e
			[], n = 0
*/

poz([], _, _, []).
poz([H|T], H, C, [C|R]):-
	!,C1 is C + 1,
	poz(T, H, C1, R).
poz([_|T], E, C, R):-
	C1 is C + 1,
	poz(T, E, C1, R).


p(L, R):-
	cauta_max(L, M),
	poz(L, M, 0, R).
