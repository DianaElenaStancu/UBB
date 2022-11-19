/*
a. sa se scrie un predicat care substituie intr-o lista un element printr-o alta lista
b. sa se elimine elementul de pe pozitiaa n-a a unei liste liniare.
*/

/*
substituie(l1l2...ln, e, l) =	[], n = 0
				l1 (+) substituie(l2...ln, e, l), daca l1 != e
				l (+) substituie(l2...ln, e, l), daca l1 = e
*/

substituie([], _, _, []):-!.
substituie([H|T], H, L, [L|R]):-!,
	substituie(T, H, L, R).
substituie([H|T], E, L, [H|R]) :-
	substituie(T, E, L, R).


/*
elimina(l1...ln, n) =		[], n = 0
				l1 (+) elimina(l2...ln, e - 1), daca e > 1
				[l2...ln], daca e = 1
*/

elimina([], _, []):-!.
elimina([_|T], 1, T):-!.
elimina([H|T], N, [H|R]):-
	N1 is N - 1,
	elimina(T, N1, R).

	
