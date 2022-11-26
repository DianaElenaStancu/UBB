%12. Se da sirul a1,..., an format din numere intregi distincte. Se cere sa se
%afiseze toate submultimile cu aspect de "munte"(o secvență se spune ca are
%aspect de "munte" daca elementele cresc pana la un moment dat, apoi descresc. De
%ex. 10 16 27 18 14 7).


% subSet - genereaza(verifica) daca o lista este submultime a unei liste
% subSet(Lista(candidat la subset),Lista(in care se verifica))
% model de flux: (i,i),(i,o)-nedeterminist

subSet([],[]):-!.
subSet([H|T],[H|Rez]):-
     subSet(T,Rez).
subSet([_|T], Rez):-
    subSet(T,Rez).


% removeAscending - elimina partea crescatoare de la inceputul unei liste
% removeAscending(List(din care se elimina), List(rezultat))
% model de flux: (i,i), (i,o)

removeAscending([H1,H2|T],Rez):-
    H1 < H2, ! ,
    removeAscending([H2|T],Rez).
removeAscending([_,H2|T],[H2|T]).

% checkDescending - verifica daca lista data este descrescatoare
% checkDescending(List)
% model de flux: (i)

checkDescending([H1,H2|T]):-
    H1 > H2,
    checkDescending([H2|T]).
checkDescending([_]).

% isMountain - verifica daca o lista data este de tip munte
% isMountain(List(lista verificata))
% model de flux: (i)

isMountain([H1,H2|T]):-
    H1 < H2,
	removeAscending([H1,H2|T],Rez),
	checkDescending(Rez).
	
% findMountain - determina sublistele cu aspect de munte din lista data
% findMountain(List)
% model de flux: (i,i), (i,o) 
    
findMountain([],[]).
findMountain([H|T],[H|Rez]):-
    isMountain(H),!,
    findMountain(T,Rez).
findMountain([_|T],Rez):-
    findMountain(T,Rez).
	
% printL - afiseaza sublistele unei liste
% printL(List)
% model de flux: (i)	

printL([H|T]):-
    write(H), nl,
    printL(T).

main(L):-
    findall(X,(subSet(L,X)),Sets),!,
	findMountain(Sets,Rez),
    printL(Rez).
