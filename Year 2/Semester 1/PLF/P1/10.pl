/*
a. sa se intercaleze un element pe pozitia a n-a a unei liste.
b. definiti un predicat care intoarce cel mai mare divizor comun al numerelor dintr-o lista.
*/

/*
inter(e, l1l2...lm, n) = 	[], m = 0
				e (+) inter(e, l1l2...lm, n), n = 0
				l1 (+) inter(e, l2...lm, n - 1), n > 0
*/


inter(_, [], _, []):-!.
inter(E, L, N, [E|R]):-
	N is 1,
	!,
	N1 is N - 1,
	inter(E, L, N1, R).
inter(E, [H|T], N, [H|R]):-
	N1 is N - 1,
	inter(E, T, N1, R).

/*
cmmdc(a, b, r) =	a, b = 0
			cmmdc(b, r, a%b), altfel 
*/

cmmdcbis(A, B, A):-
	B is 0, !.
cmmdcbis(A, B, R):-
	X is mod(A, B),
	cmmdcbis(B, X, R).
	
/*
cmmdclista(l1..ln) =	1, n = 0
			cmmdc(l1, cmmdclista(l2...ln)), n > 0
*/
cmmdclista([H], H):-!.
cmmdclista([H|T], R):-
	cmmdclista(T, R1),
	cmmdcbis(H, R1, R).


