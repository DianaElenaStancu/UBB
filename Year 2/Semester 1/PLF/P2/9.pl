% a)Dandu-se  o  lista  liniara  numerica,  sa  se  stearga  toate  secventele  de valori consecutive.
% Ex: sterg([1, 2, 4, 6, 7, 8, 10], L) va produce L=[4, 10].

% b)Se  da  o  lista  eterogena,  formata  din  numere  intregi  si  liste  de  numere intregi.  Din  fiecare  sublista  sa  se  stearga  toate  secventele  de  valori consecutive. 
% De ex:[1, [2, 3, 5], 9, [1, 2, 4, 3, 4, 5, 7, 9], 11, [5, 8, 2], 7] =>[1, [5], 9, [4, 7, 9], 11, [5, 8, 2], 7]


% a)
% sterg(l1l2..ln) =	[], n = 0
%			[l1], n = 1
%			[], n = 2 si l1 = l2 - 1
%			sterg(l2...ln), l1 = l2 - 1 = l3 - 2
%			sterg(l3...ln), l1 = l2 - 1 != l3 - 2
%			l1 (+) sterg(l2...ln), altfel

% sterg(L: lista, R: lista) - determinist
% model de flux: (i,i) sau (i,o)
% L - lista liniara din care eliminam toate secventele de valori consecutive
% R - lista rezultat

sterg([],[]).
sterg([H], [H]).
sterg([H1, H2], []):- 
			H1 is H2 - 1.
sterg([H1,H2,H3|T], R):- 
			H1 is H2 - 1,
			H1 is H3 - 2,
			sterg([H2,H3|T], R).
sterg([H1,H2,H3|T], R):-
			H1 is H2 - 1,
			not(H1 is H3 - 2),
			sterg([H3|T], R).
sterg([H1,H2|T], [H1|R]):-
			not(H1 is H2 - 1),
			sterg([H2|T], R).

% b)
% sterg_eterogen(l1l2..ln) =	[], n = 0
%				sterg(l1) (+) sterg_eterogen(l2..ln) , l1 = lista si n > 0
%				l1 (+) sterg_eterogen(l2..ln), l1 != lista si n > 0

% sterg_eterogen(L: lista, R: lista) - determinist
% model de flux: (i,i) sau (i,o)
% L - lista eterogena din care eliminam toate secventele de valori consecutive din fiecare sublista
% R - lista rezultat

sterg_eterogen([],[]).
sterg_eterogen([H|T], [S|R]):- 
				is_list(H),
				!,
				sterg(H,S),
				sterg_eterogen(T, R).
sterg_eterogen([H|T], [H|R]):-
				sterg_eterogen(T, R).

/*
elim([], []).
elim([H], [H]).
elim([H1,H2], []):- H1 < H2, !.
elim([H1,H2,H3|T], R):- 
			H1 < H2,
			H2 < H3,
			!,
			elim([H2,H3|T], R).
elim([H1,H2,H3|T], R):- 
			H1 < H2,
			H2 >= H3,
			!,
			elim([H3|T], R).
elim([H1,H2|T], [H1|R]):- 
			H1 >= H2,
			!,
			elim([H2|T], R).
*/
