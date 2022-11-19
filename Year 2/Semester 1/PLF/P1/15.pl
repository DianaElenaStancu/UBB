/*
a. true - daca lista are un numar par de elemente. sa nu se numere lista
b. sa se elimine prima aparitie a elementului minim dintr-o lista 
*/

par([]):-!.
par([_, _ | T]):-
	par(T).



elimina([H|T], H, T):-!.
elimina([H|T], E, [H|R]):-
	elimina(T, E, R).


minim([H], H):-!.
minim([H|T], M):-
	minim(T, M1),
	M1 < H,
	!,
	M is M1.
minim([H|T], M):-
	minim(T, M1),
	M1 > H,
	M is H.

