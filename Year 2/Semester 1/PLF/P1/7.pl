/*
a. sa se scrie un predicat care intoarce reuniunea a doua multimi
b. sa se scrie un predicat care, primind o lista, intoarce multimea tuturor perechilor din lista. De ex cu [a,b,c,d] va produce [[a,b], [a,c], [a,d], [b,c], [b,d], [c,d]]
*/
/*
apartine(e, l1...ln) =		false, n = 0
				true, e = l1
				apartine(e, l2...ln), altfel
*/

apartine(E, [E|_]):-!.
apartine(E, [_|T]):-
	apartine(E, T).


/*
reuniune(l1..ln, k1...km) =	l1...ln, m = 0
				k1 (+) reuniune(l1...ln, k2...km), daca apartine(k1, l1...ln) = false
				reuniune(l1...ln, k2...km), altfel
*/

reuniune(L, [], L):-!.
reuniune(L, [H|T], R):-
	apartine(H, L),
	!,
	reuniune(L, T, R).
reuniune(L, [H|T], [H|R]):-
	reuniune(L, T, R).


/*
pereche(l1l2..ln, e) = [l1, e] (+) pereche(l2...ln, e).
*/
pereche([H], E, [[E, H]]):-!.
pereche([H|T], E, P):- 
	pereche(T, E, P1),
	P = [[E, H] | P1].

/*	
perechi(l1l2...ln) =	[], n = 0 
			pereche(l2...ln, l1) (+) perechi(l2...ln), atfel 
*/

perechi([A, B], R):-
	!,
	R = [[A,B]].
perechi([H|T], R):-
	pereche(T, H, X),
	perechi(T, R1),
	R = [X | R1].
