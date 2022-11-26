/*
comb(l1l2..ln, k) = 	[l1],	k = 1
			comb(l2...ln, k)
			l1 (+) comb(l2...ln, k - 1), k > 1
*/

comb([H], 1, [H]).
comb([_|T], K, R):-
	comb(T, K, R).
comb([H|T], K, [H|R]):-
	K1 is K - 1,
	comb(T, K1, R).

/*
subm(l1l2..ln) =	[],   n = 0
                        subm(l2...ln)
                        l1 (+) subm(l2...ln)
*/
s([], []).
s([_|T], R):- s(T, R).
s([H|T], [H|R]):- s(T, R).


/*
inv_numar(nr, nri) = 	nri, nr = 0
			inv(nr/10, nri*10+nr%10), altfel

*/

%inv_numar(Nr: int, NrI: int, Rez: int)
%Nr - numarul care trebuie inversat
%NrI - variabila colectoare in care retinem rezultatul partial
%Rez - rezultatul
%model de flux (i, i, o), (i, i, i)

inv_numar(0, NrI, NrI).
inv_numar(Nr, NrI, Rez):-
	Nr > 0,
	Cifra is mod(Nr,10),
	NrINew is NrI * 10 + Cifra,
	NrNew is Nr div 10,
	inv_numar(NrNew, NrINew, Rez).
