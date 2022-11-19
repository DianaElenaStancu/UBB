/*
a. sa se scrie un predicat care sa elimine toate elementele care se repeta dintr-o lista
b. sa se elimine toate aparitiile elementului maxim dintr-o lista de numere intregi
*/

/*
nrAp(e, l1l2...ln) = 	0, n = 0
			1 + nrAp(e, l2...ln), e = l1
			nrAp(e, l2...ln), e != l1
*/
nr(_,[],0):-!.
nr(E, [E|T], C):-
	!,
	nr(E, T, C1),
	C is C1 + 1.
nr(E, [_|T], C):-
	nr(E, T, C).

/*
del(e, l1l2...ln) = 	[], n = 0
			l1 (+) del(e, l2...ln), l1 != e
			del(e, l2...ln), l1 = e
*/

del(_,[], []):-!.
del(E, [E|T], R):-
	!,
	del(E, T, R).
del(E, [H|T], [H|R]):-
	del(E, T, R).

/*
rep(l1l2...ln) = 	[], n = 0
			rep(sterge(l1, l2..ln)), nr(l1, l2...ln) >= 1
			l1 (+) rep(l2...ln), altfel
*/
rep([], []):-!.
rep([H|T], R):-
	nr(H, T, X),
	X >= 1,
	!,
	del(H, T, T1),
	rep(T1, R).
rep([H|T], [H|R]):-
	rep(T, R).


/*
max(l1l2...ln) = 	l1, n = 1
			l1, l1 > max(l2...ln),
			max(l2...ln), l1 <= max(l2...ln)
*/
max([H],H):-!.
max([H|T], M):-
	max(T, M1),
	H > M1,
	!,
	M is H.
max([H|T], M):-
	max(T, M1),
	M is M1.

elmax([], []):-!.
elmax(L, R):-
	max(L, M),
	del(M, L, R).



