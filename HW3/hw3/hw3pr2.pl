%Elliott Dobbs
%CSCE 420
%Due: November 15, 2017
%hw3pr2.pl

my_max([], -2147483648).
my_max([X], X).
my_max(L, [A, Y]) :- member([_, Y], L), forall(member([A, _], L), A\==Y), !.

remove_unless_root(L, M, L) :- 		select([A, M], L, L2), 
					forall(member([N, O], L2), O\==A), !.
remove_unless_root(L, M, P) :- 		select([_, M], L, P), !.

my_sort([], []).
my_sort([X], [X]).
my_sort(U, S, L) :- 	my_max(L, [A, M]), 
			select(M, U, U2),
			my_sort(U2, S2, R), 
			append(S2, [M], S).

removeDup([], []).
removeDup([H|T], [H|T1]) :- delete(T, H, R), removeDup(R, T1).

my_topo_sort(L, L3) :- flatten(L, L2), removeDup(L2, L3).


