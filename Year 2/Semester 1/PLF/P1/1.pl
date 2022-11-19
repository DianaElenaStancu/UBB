/*
a. sa se scrie un predicat care intoarce diferenta a doua multimi.
b. sa se scrie un predicat care adauga intr-o lista dupa fiecare element par valoarea 1.
*/

/*
apare(e, l1l2..ln) = 	false, n = 0
			true, e = l1, n > 0
			apare(1, l2..ln), e != l1, n > 0
apare(E: integer, L: list)
modele de flux: (i,i) - determinist
E - elementul pe care il cautam in lista
L - lista omogena de numere in care cautam elementul E
*/

apare(E, [E|_]):- !.
apare(E, [_|L]):- apare(E, L).


/*
dif(l1l2...ln, k1k2..km) = 	[], n = 0
				l1 (+) dif(l2...ln, k1...km), apare(l1, k1..km) = false, n != 0
				dif(l2...ln, k1...km), apare(l1, k1...km) = true, n != 0

dif(L: list, K: list, R: list)
modele de flux: (i,i,o), (i,i,i) - deterministe
L - lista omogena de elemente
K - lista omogena de elemente
R - lista rezultata in urma diferentei dintre L si K (L-K)
*/

dif([], _, []).
dif([H|T], K, [H|R]):-
	not(apare(H, K)),
	!,
	dif(T, K, R).
dif([_|T], K, R):-
	dif(T, K, R).

/*
adaugaPar(l1...ln) = 	[], n = 0
			l1 (+) 1 (+) adaugaPar(l2...ln), l1 % 2 = 0 si n > 0
			l1 (+) adaugaPar(l2...ln), l1 % 2 = 0 si n >0

adaugaPar(L: list, R: list)
modele de flux: (i,i), (i,o) - deterministe
L - lista pe care parcurgem
R - lista rezultata in urma adaugarii elementului 1 dupa fiecare element din lista L
*/

adaugaPar([], []).
adaugaPar([H|T], [H,1|R]):-
		H mod 2 =:= 0,
		!,
		adaugaPar(T,R).
adaugaPar([H|T], [H|R]):-
		adaugaPar(T, R). 
