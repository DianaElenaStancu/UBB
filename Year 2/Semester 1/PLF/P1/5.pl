/*
definiti un predicat care, dintr-o lista de atomi, produce o lista de perechi (atom n), unde atom apare in lista initiala de n ori
ex: numar([1,2,1,2,1,3,1), X) va produce X = [[1,4], [2,2], [3,1]]
*/
/*
nrAp(l, l1...ln) = 	0, n = 0
			1 + nrAp(l, l2...ln), l = l1
			nrAp(l,l2...ln), altfel
*/
nrAp(_, [], 0):-!.
nrAp(E, [E|T], C):-
	!,
	nrAp(E, T, C1),
	C is C1 + 1.
nrAp(E,[_|T], C):-
	nrAp(E, T, C).


/*
sterge(l, l1...ln) = 	[], n = 0
			l1 (+) sterge(l, l2...ln), l1 != l
			sterge(l, l2...ln), altfel
*/
	sterge(_, [], []):-!.
sterge(L, [L|T], R):- 
	!,
	sterge(L, T, R).
sterge(L, [H|T], [H|R]):-
	sterge(L, T, R).


/*
numar(l1l2...ln) =	[], n = 0
			[l1, nrAp(l1, l1l2...ln)] + numar(sterge(l1, l2...ln)), altfel
*/

numar([], []):-!.
numar([H|T], R):-
	nrAp(H, [H|T], C),
	sterge(H, T, T1),
	numar(T1, R1),
	R = [[H, C] | R1].


