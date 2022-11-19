/*
a. sa se calculeze un predicat are sa testeze daca o lista formata din numere intregi are aspect de vale ex. 10 8 6 9 11 13
b. sa se calculeze suma alternanta a elementelor unei liste
*/

/*
is_vale(l1l2...ln, f) = 	is_vale(l2...ln, 0), l1 < l2 si f = 0
				is_vale(l2...ln, 1), l1 > l2 si f = 1
				false

is_vale(L: list, F: integer)
L - lista pe care o verificam daca are aspect de vale
F - flag care poate fi:	-1 - initial
			0 - daca este descrescatoare
			1 - daca este crescatoare
*/

is_vale([_], 1):-!.
is_vale([H1, H2 | T], F) :-
	H1 > H2,
	F < 1, 
	!, 
	is_vale([H2 | T], 0).
is_vale([H1, H2 | T], F) :-
	H1 < H2,
	F > -1,
	is_vale([H2 | T], 1).

is_vale_p(L) :- is_vale(L, -1).


/*
suma_alt(l1l2..ln, p) = 0, n = 0
			l1 + suma_alt(l2...ln, 1), n > 0 si p = 0
			suma_alt(l2...ln, 0) - l1, n > 0 si p = 1
			
0 = poz para = adunare
1 = poz impara = scadere
*/

suma_alt([], _, 0):-!.
suma_alt([H | T], 0, S) :-
	!,
	suma_alt(T, 1, S1),
	S is S1+H.
suma_alt([H|T], 1, S) :-
	suma_alt(T, 0, S1),
	S is  S1-H.
