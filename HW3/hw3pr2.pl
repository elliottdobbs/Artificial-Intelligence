%Elliott Dobbs
%CSCE 420
%Due: November 15, 2017
%hw3pr2.pl

my_max([], -2147483648).
my_max([X], X).
%my_max(L, X) :- forall(member([]))
my_max(L, [A, Y]) :- member([_, Y], L), forall(member([A, _], L), A\==Y), !.

remove_unless_root(L, [A, M], L) :- 	select([A, M], L, L2), 
					forall(member([N, O], L2), O\==A), !.
remove_unless_root(L, [A, M], P) :- 	removeAll(L, [A, M], P).

removeAll(L, [A, M], P) :- 	select(L, [_, M], L2),
				removeAll(L, [A, M], L2).
removeAll(L, [A, M], L).

my_sort([X], [X]).
my_sort(U, S, L) :- 	my_max(L, [A, M]), 
			select(M, U, U2), 
			remove_unless_root(L, [A, M], R), 
			my_sort(U2, S2, R), 
			append(S2, [M], S).

removeDup([], []).
removeDup([H|T], [H|T1]) :- delete(T, H, R), removeDup(R, T1).

my_topo_sort(L, X) :- flatten(L, L2), removeDup(L2, L3), my_sort(L3, X, L).


