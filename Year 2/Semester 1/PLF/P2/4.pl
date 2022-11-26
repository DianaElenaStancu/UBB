/*
sa se interclaseze fara pastrare dublurilor doua liste sortate


inter(l1...lk, m1...mn) =	m1...mn, k = 0
				l1...lk, n = 0
				l1 (+) inter(l2..lk, m1...mn), l1 < m1
				m1 (+) inter(l1..lk, m2...mn), l1 >= m1
*/

inter([], M, M):-!.
inter(L, [], L):-!.
inter([H1|T1], [H2|T2], [H1|R]):-
	H1 < H2, !,
	inter(T1, [H2|T2], R).
inter(L, [H2|T2], [H2|R]):-
	inter(L, T2, R).


