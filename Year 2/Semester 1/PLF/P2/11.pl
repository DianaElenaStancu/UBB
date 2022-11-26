/*
se da o lista de numere intregi. se cere sa se scrie de 2 ori n lista fiecare numar prim
*/

/*
prim(nr, div) = 	true, div >= nr
			prim(nr, div + 1), nr%div != 0
			false
			
*/

prim(N, D):- N =< D, !.
prim(N, D):-
	mod(N, D) =\= 0,
	D1 is D + 1,
	prim(N, D1).


lista([], []).
lista([H|T], [H, H|R]):-
	prim(H, 2),
	!,
	lista(T, R).
lista([H|T], [H|R]):-
	lista(T, R).
