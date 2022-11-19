/*
a. sa se scrie un predicat care inlocuieste intr-o lista un element cu un altul
b. sa se construiasca sublista (lm,...,ln) din (l1...lk).
*/


/*
subst(l1...ln, e1, e2) = 	[], n = 0
				e2 (+) subst(l2...ln), l1 = e1
				l1 (+) subst(l2...ln), altfel
*/

subst([], _, _, []):-!.
subst([E1|T], E1, E2, [E2|Rez]):- !, 
	subst(T, E1, E2, Rez).
subst([H|T], E1, E2, [H|Rez]):-
	subst(T, E1, E2, Rez).

/*
constr(l1...lk, m, n, c) = 	[], c > n
				l1 (+) constr(l2...lk, m, n, c + 1), c >= m
				constr(l2...lk, m, n, c + 1), altfel
*/

constr(_, _, N, C, []):-
	C > N, !.
constr([H|T], M, N, C, [H|R]):-
	C >= M,
	!,
	C1 is C + 1,
	constr(T, M, N, C1, R).
constr([_|T], M, N, C, R):-
	C1 is C + 1,
	constr(T, M, N, C1, R).
