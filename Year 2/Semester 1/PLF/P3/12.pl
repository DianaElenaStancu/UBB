/*
12. se da sirul a1,..,an format din numere intregi distincte. Se cere sa se afiseze toate submultimile cu aspect de "munte"(o secventa se spune ca are aspect de "munte" daca elementele cresc pana la un moment dat, apoi descresc. De ex. 10 16 27 18 14 7).
*/

/*
is_munte(l1...ln, flag) = 	true, n = 1, flag = 1
				is_munte(l2...ln, 0), n > 1, flag < 1, l1 < l2
				is_munte(l2...ln, 1), n > 1, flag > -1, l1 > l2
				false, altfel

is_munte(L:list, F:int)
L - lista omogena pe care o verificam daca are aspect de munte
F - flag care poate fi: -1 initial
			0, lista e crescatoare
			1, lista e descrescatoare
modele de flux: (i,i) - determinist
*/

is_munte([_], 1):-!.
is_munte([H1, H2|T], F):-
	F < 1, 
	H1 < H2,
	is_munte([H2|T], 0).
is_munte([H1, H2|T], F):-
	F > -1,
	H1 > H2, 
	is_munte([H2|T], 1).


/*
subm(l1, l2...ln) = 	[], n = 0
			subm(l2...ln)
			l1 (+) subm(l2...ln)

subm(L: list, Subm: list)
L - lista din care generam submultimi
Subm - submultimile care se pot forma din lista L
modele de flux: (i,o) nedeterminist, (i,i) - determinist
*/ 
subm([], []).
subm([_|T], S):-
	subm(T, S).
subm([H|T], [H|S]):- 
	subm(T, S).

/*
submultimi(l1l2...ln) = liste_munte(U(subm(L)))
 
submultimi(L: list, LRez: list of lists)
L - lista din care generam multimi
LRez - lista care contine toate submultimile cu aspect de "munte" din L
modele de flux: (i,o) si (i,i) - determinist
*/

submultimi(L, LRez):- 
		findall(S, subm(L, S), LSubm),
		liste_munte(LSubm, LRez).

/*
liste_munte(l1l2...ln) = 	[], n = 0
				l1 (+) liste_munte(l2...ln), daca n > 0 si is_munte(l1) = true
				liste_munte(l2...ln), altfel

liste_munte(L: list of lists, LRez: list of lists)
L - lista de liste
LRez - lista care contine listele de aspect de munte
modele de flux: (i,o) si (i,i) - determinist
*/

liste_munte([], []):-!.
liste_munte([H|T], [H|Rez]):-
		is_munte(H, -1),
		!,
		liste_munte(T, Rez).
liste_munte([_|T], Rez):-
		liste_munte(T, Rez).
		

			
