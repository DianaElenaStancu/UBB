inverseaza([], C, C).
inverseaza([H | T], C, R) :-
        inverseaza(T, [H | C], R).


secv([], C, Lcr, _, Lmax, C) :-
        Lcr > Lmax, !.
secv([], _, Lcr, M, Lmax, M) :-
        Lcr =< Lmax, !.
secv([H | T], C, Lcr, M, Lmax, R) :-
        H mod 2 =:= 0, !,
        Lcr1 is Lcr + 1,
        secv(T, [H | C], Lcr1, M, Lmax, R).
secv([H | T], C, Lcr, _, Lmax, R) :-
        H mod 2 =:= 1,
        Lcr > Lmax, !,
        secv(T, [], 0, C, Lcr, R).
secv([H | T], _, Lcr, M, Lmax, R) :-
        H mod 2 =:= 1,
        Lcr =< Lmax,
        secv(T, [], 0, M, Lmax, R).

secventa(L, R) :-
        secv(L, [], 0, [], 0, R1),
        inverseaza(R1, [], R).
