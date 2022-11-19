adaug(E, [],[E]).
adaug(E, [H|T], [H|Rez]) :-adaug(E, T, Rez).

adaug2([],E, [E]).
adaug2([H|T], E, [H|Rez]) :-adaug2(T, E, Rez).
