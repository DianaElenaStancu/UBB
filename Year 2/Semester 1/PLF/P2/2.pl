/*
sa se sorteze o lista cu pastrarea dublurilor
*/

/*
inserare(l1...ln, e) = 		[e], n = 0
				e (+) l1l2...ln, daca e <= l1
				l1 (+) inserare(l2...ln, e), altfel
*/

inserare(E, [], [E]):-!.
inserare(E, [H | T], [E, H | T]):-
	E =< H, !.
inserare(E, [H|T], [H|R]):-
	E > H,
	inserare(E, T,  R).

i(E, [], [E]):-!.
i(E, [H | T], [E, H | T]):-
        E < H, !.
i(E, [H|T], [H|T]):-
	E =:= H, !.
i(E, [H|T], [H|R]):-
        E > H,
        i(E, T,  R).
/*
sorteaza(l1...ln) = 	[], n = 0
			inserare(l1, sorteaza(l2...ln)), altfel
*/

sorteaza([], []).
sorteaza([H|T], R):-
	sorteaza(T, R1),
	inserare(H, R1, R).
