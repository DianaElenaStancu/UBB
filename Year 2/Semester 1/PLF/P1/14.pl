/*
a. sa se scrie un predicat care testeaza egalitatea a doua multimi, fara a se folosi diferenta 
b. definiti un predicat care selecteaza al n-lea element al unei liste
*/

exista([E|_], E) :- !.
exista([_|T], E) :- exista(T, E).

/*
egale(l1...ln, L) = 	egale(l2...ln, L), exista(L, l1) = true, n > 0
			true, n = 0
			false, altfel
*/

inclus([], _):-!.
inclus([H|T], L):-
	exista(L, H),
	inclus(T, L).

egale(L1, L2):- 
	inclus(L1, L2),
	inclus(L2, L1).

element([H|_], 1, H):-!.
element([_|T], N, E):-
	N1 is N - 1,
	element(T, N1, E).
