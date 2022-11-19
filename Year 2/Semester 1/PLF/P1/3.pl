/*
a. sa se scrie un predicat care transforma o lista intr-o multime, in ordinea primei aparitii
b. sa se scrie o functie care descompune o lista de numere intr-o lista de numere de forma [lista-de-numere-pare lista-de-numere-impare], deci lista cu doua elemente care sunt liste de numere intregi, si va intoarce si numarul elementelor pare si impare
*/
/*
exista(l1..ln, e) = 	false, n = 0
			true, e = l1
			exista(l2...ln, e), e != l1
*/
exista([E|_], E):-!.
exista([_|T], E):- exista(T, E).
	

/*
sterge(l1l2...ln, e) = 	[], n = 0
			sterge(l2...ln), l1 = e
			l1 (+) sterge(l2...ln), l1 != e
*/

sterge([], _, []).
sterge([H|T], E, [H|R]):-
	E =\= H,
	!,
	sterge(T, E, R).
sterge([_|T], E, R):-
	sterge(T, E, R).


/*
multime(l1l2...ln) = 	l1 (+) multime(sterge(l1, l2...ln)), n > 0
			[], n = 0
*/

multime([], []).
multime([H|T], [H|R]) :- 
	sterge(T, H, X),
	multime(X, R).

/*
lung(l1..ln) =	1 + lung(l2...ln), n > 0
		0
*/

lung([], 0):-!.
lung([_|T], C):-
	lung(T, C1),
	C is C1 + 1.

/*
adaugaSf(e, l1...ln) =	[e], n = 0
			l1 (+) adaugaSf(e, l2...ln), astfel

*/
adaugaSf(E, [], [E]):-!.
adaugaSf(E, [H|T], [H|R]) :-
			adaugaSf(E, T, R).


/*
descompunere(l1l2...ln, cPar, cImp) =	[], 0, 0, daca n = 0
					l1 (+) descompunere(l2...ln, cPar + 1, cImp), l1 este par
					descompunere(l2...ln, cPar, cImp + 1) (+) l1, l1 este impar
*/
descompunere([], 0, 0, []):-!.
descompunere([H|T], Cp, Ci, [H|R]):-
		H mod 2 =:= 0,
		!,
		descompunere(T, Cp1, Ci, R),
		Cp is Cp1 + 1.
descompunere([H|T], Cp, Ci, R):-
		descompunere(T, Cp, Ci1, X),
		adaugaSf(H, X, R),
		Ci is Ci1 + 1.
		
