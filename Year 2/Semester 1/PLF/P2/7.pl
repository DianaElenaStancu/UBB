/*
a) definiti un predicat care determina produsul unui numar reprezentat cifra cu cifra intr-o lista cu o anumita cifra de exemplu [1 9 3 5 9 9] * 2 = [3 8 7 1 9 8]
*/
/*
adaugaSf(l1...ln, e) = 	[e], n = 0
			l1 (+) adaugaSf(l2...ln, e), altfel
*/



adaugaSf([], E, [E]).
adaugaSf([H|T], E, [H|R]):-
		adaugaSf(T, E, R).


/*
invers(l1...ln) = 	[], n = 0
			invers(adaugaSf(l2...ln, l1)), n > 0

*/

invers([], []).
invers([H|T], R) :-
	invers(T, R1),
	adaugaSf(R1, H, R).

/*
inmult(l1...ln, c, f) = 	[f], n = 0 si f > 0
				[], n = 0 si f = 0
				(l1*c+f)%10 (+) inmult(l2...ln, c, (l1*c+f)/10), altfel 
*/  

inmult([], _, F, [F]):- F > 0, !.
inmult([], _, 0, []):-!.
inmult([H|T], C, F, R):-
	C1 is mod(H*C+F, 10),
	F1 is div(H*C+F, 10),
	inmult(T, C, F1, R1),
	R = [C1|R1].

/*
inmult_p(
*/
inmult_p(L, C, R):-
	invers(L, L1),
	inmult(L1, C, 0, R1),
	invers(R1, R).
	
