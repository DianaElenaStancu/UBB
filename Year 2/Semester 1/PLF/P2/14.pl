/*
definiti un predicat care determina predecesorul unui numar rprezentat cifra cu cifra intr-o lista

ex: [1, 9, 3, 6, 0, 0] => [1, 9, 3, 5, 9, 9]
*/

/*
inv(l1...ln, c = []) = 		c, n = 0
				inv(l2...ln, l1 (+) c), n > 0
*/

inv([], C, C).
inv([H|T], C, R):-
	inv(T, [H|C], R).

/*
scade(l1...ln, f) = 	[],n=0
			(l1+10+f)%10 (+) scade(l2...ln, (l1+10+f)/10-1), f = -1
*/
scade([0], _, []):-!.
scade([1], -1, []):-!.
scade([], _,  []).
scade([H|T], F,  R):-
	V1 is (H+10+F),
	V2 is mod(V1, 10),
	F1 is div(V1, 10)-1,
	scade(T, F1, R1),
	R = [V2|R1].

/*
pred(L) = inv(scade(inv(L)))
*/
pred(L, R):-
	inv(L,[], L1),
	scade(L1, -1, R1),
	inv(R1,[], R).
	
