secvente([], []).
secvente([_|T], Rez):-
	secvente(T, Rez).
secvente([H|T], [H|Rez]):-
	prefixe(T, Rez).

prefixe(_, []).
prefixe([H|T], [H|Rez]):-
	prefixe(T, Rez).


cevreaDiana(L, Rez):-
	findall(AUX, secvente(L, AUX), Rez1),
	cutFirst(Rez1, Rez).

cutFirst([_|T], T).
