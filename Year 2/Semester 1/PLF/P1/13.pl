/*
sa se scrie un predicat care transforma o lista intr-o multime, in ordinea ultimei aparitii.
ex. [1,2,3,1,2] transformat in [3,1,2]
*/

/*
is_member(l1..ln, e) = 	false, n = 0
			is_member(l2...ln, e), l1 != e
			true

*/
is_member([E|_], E):-!.
is_member([_|T], E):-
	is_member(T, E).

mult([],[]):-!.
mult([H|T], [H|R]):-
	not(is_member(T, H)),
	!,
	mult(T, R).
mult([_|T], R):-
	mult(T, R).
	
