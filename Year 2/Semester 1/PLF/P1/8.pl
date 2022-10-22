/*
ENUNT PROBLEMA 8 
a. Sa se scrie un predicat care testeaza daca o lista este multime.

b. Sa se scrie un predicat care elimina primele 3 aparitii ale unui element intr-o lista. Daca elementul apare mai putin de 3 ori, se va elimina de cate ori apare.
*/

/*
a.

nuApare(L = l1l2l3..ln, X)  = 	true, L = vid
				false, l1 == X
				nuApare(l2l3...ln, X), altfel

esteMultime(L = l1l2l3..ln) =	true, L = vid
				false, nuApare(l1, l2l3..ln) == false
				esteMultime(l2l3...ln), altfel
								
*/


/*
nuApare(L:lista, I: intreg)
L - lista in care verificam daca apare sau nu I
I - numar intreg, il vom cauta in lista
model de flux: nuApare(i, i)
*/
nuApare([],_):- !.
nuApare([Cap|Coada], X):- X \== Cap,
	nuApare(Coada, X).


/*
esteMultime(L: lista)
L - lista care va fi verificata daca e multime sau nu
model de flux: esteMultime(i)
*/

esteMultime([]):- !.
esteMultime([Cap|Coada]) :- nuApare(Coada, Cap),
	esteMultime(Coada).


/*
elimina(L1 = l1l2...ln, Element, L2, N = 3) =	elimina(L1 = l2...ln, Element, L2 = L1, N - 1), l1 = Element si N > 0	
						elimina(L1 = l2...ln, Element, L2 = l1l2...ln, N), l1 != Element si N > 0 
*/
/*
elimina(L1:lista, Element:intreg, L2:lista)
L1 - lista din care trebuie eliminata elementul Element de 3 ori
Element - numar intreg, cel care trebuie eliminat
L2 - lista obtinuta in urma eliminarii de 3 ori a elementului Element
model de flux: elimina(i,i,o) sau elimina(i,i,i)
predicatul contine si al patrulea element care este numarul de aparitii al elementului Element
*/


elimina(L1,Element,L2):-elimina(L1,Element,L2,3).
elimina([],_,[],_):- !.
elimina(L2,_,L2,0):- !.
elimina([Cap|Coada],Element,L2,N):- Cap == Element,
    N1 is N-1,
    elimina(Coada,Element,L2,N1),!.
elimina([Cap|Coada],Element,[Cap|L2],N):-elimina(Coada,Element,L2,N).
