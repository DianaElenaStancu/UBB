/*
a. sa se scrie un predicat care determina cel mai mic multiplu comun al elementelor unei liste formate din numere intregi
b. sa se scrie un predicat care adauga dupa 1-ul, al 2-lea, al 4-lea, al 8-lea,....element al unei liste o valoare v data.
*/
/*
cmmdc(a, b) =   a, b = 0
		cmmdc(b, a%b), altfel 
cmmdc(A: integer, B: integer, R: integer)
modele de flux: (i,i,i), (i,i,o) - deterministe
A - numar intreg
B - numar interg
R - cel mai mare divizor comun dintre A si B
*/

cmmdc(A, 0, A):- !.
cmmdc(A, B, R):-
	B > 0,
	X is mod(A, B),
	cmmdc(B, X, R).

/*
cmmmc(a, b) = a * b / cmmdc(a,b).
cmmmc(A: integer, B: integer, R: integer)
modele de flux: (i,i,o), (i,i,i) - deterministe
A - numar intreg
B - numar intreg
R - cel mai mic multiplu comun dintre A si B
*/
cmmmc(A, B, R):-
	cmmdc(A, B, R1),
	R is A * B / R1.

/*
cmmmcLista(l1l2...ln) = 	0, n = 0
				l1, n = 1
				cmmmc(l1, cmmmcLista(l2...ln)), altfel		  
cmmmcLista(L: list, R: integer)
modele flux: (i,i), (i,o) - deterministe
L - lista din care calculam cmmmc dintre toate elementele ei
R - rezultatul
*/
cmmmcLista([], 0).
cmmmcLista([H], H):- !.
cmmmcLista([H|T], R):-
	cmmmcLista(T, X),
	cmmmc(H, X, R).

/*
put2(a) = 	true, a == 1
		false, a % 2 != 0
		put2(a/2), altfel
put2(A: integer)
modele de flux: i - determinist
A - numarul pe care il verificam daca este putere a lui 2
*/

put2(1) :- !.
put2(X) :-
	X mod 2 =:= 0,
	Y is X/2,
	put2(Y).

/*
adauga(l1...ln, v, contor) =	[], n = 0
				l1 (+) v (+) adauga(l2..ln, v, contor + 1), put2(contor) = true
				l1 (+) adauga(l2...ln, v, contor + 1), altfel 

adauga(L: list, V: integer, C: integer, R: list)
modele de flux: (i,i,i,i) sau (i,i,i,o) - deterministe
L - lista careia ii adaugam elementul v dupa 1-ul, al 2-lea, al 4-lea, al8-leaelement si tot asa
V - elementul pe care il adaugam conform proprietatii de mai sus
C - un contor care indica la al catelea element suntem
R - lista rezultata
*/

adauga([], _, _, []):- !.
adauga([H|T], V, C, [H, V|R]) :-
	put2(C),
	!,
	C1 is C + 1,
	adauga(T, V, C1, R).
adauga([H|T], V, C, [H|R]):-
	C1 is C + 1,
	adauga(T, V, C1, R).

adaugaPrincipal(L, V, R) :- adauga(L, V, 1, R).

	
