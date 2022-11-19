/*
a. sa se scrie un predicat care intoarce intersectia a doua multimi
b. sa se construiasca lista (m,...,n), adica multimea numerelor intregi din intervalul [m, n].
*/

/*
inter(l1..ln, k1...kn) =	[], n = 0
				inter(l2...ln, k1...km), member(l1, k1..km) = false, n > 0
				l1 (+) inter(l2...ln, k1..km), member(l1,k1...km) = true, n > 0
*/

inter([], _, []):-!.
inter([H|T], L, R):-
	not(member(H, L)),
	!,
	inter(T, L, R).
inter([H|T], L, [H|R]):-
	inter(T, L, R).

/*
constr(m, n) = 	[], m = n + 1
			c (+) constr(m + 1, n), altfel
*/

constr(M, N, []):-
	M > N, !.
constr(M, N, [M | R]):-
	M1 is M + 1,
	constr(M1, N, R).
	
	
