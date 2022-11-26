/*
sa se adauge dupa fiecare element dintr-o lista divizorii acestuia
*/

/*
div(n, d) = 	d, n%d == 0
		div(n, d + 1)
		stop, n <= d
*/
 
div(N, D, D):- 0 is mod(N, D).
div(N, D, R):-
	div(N,2) >= D,
	D1 is D + 1,
	div(N, D1, R).

/*
concat(l1...ln, L2) =	L2, n = 0
			l1 (+) concat(l2..ln, L2), altfel 	
*/

concat([], L2, L2).
concat([H|T], L2, [H|R]):-
	concat(T, L2, R).

/*
constr(l1...ln) =	[], n = 0
			l1 (+) findall(div(l1, 2, d)) (+) constr(l2..ln)
*/

constr([], []).
constr([H|T], R):-
	findall(D,div(H, 2, D),C),
	constr(T, R1),
	concat(C, R1, R2),
	R = [H|R2].	
