/*
sa se inlocuiasca elementul maxim dintr-o lista cu un element V dat
*/
/*
max(a, b) = 	a, daca a < b
		b, altfel
*/

max(A, B, A):-
	B =< A, !.
max(_, B, B).


/*
cauta_max(l1..ln) = 	l1, n = 0
			max(l1, cauta_max(l2...ln)), altfel		
*/

c_max([H], H):-!.
c_max([H|T], R):-
	c_max(T, R1),
	max(H, R1, R).

/*
inlocuieste(l1...ln, e, v) = 	[], n = 0
				v (+) inlocuieste(l2...ln), daca e = l1
				l1 (+) inlocuieste(l2...ln), altfel
*/

inlocuieste([], _, _, []).
inlocuieste([H|T], H, V, [V|R]):-
	!, inlocuieste(T, H, V, R).
inlocuieste([H|T], E, V, [H|R]):-
	inlocuieste(T, E, V, R).

/*
pp(l, v) = inlocuieste(l, c_max(l), v)
*/

pp(L, V, R) :-
	c_max(L, M),
	inlocuieste(L, M, V, R).
