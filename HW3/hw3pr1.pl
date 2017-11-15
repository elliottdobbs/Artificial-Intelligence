%Elliott Dobbs
%CSCE 420
%Due: November 15, 2017
%hw3pr1.pl

my_max([], -2147483648).
my_max([X], X).
my_max(L, X) :- member(X, L), forall(member(Y, L), X>= Y).

my_sort([X], [X]).
my_sort(U, S) :- my_max(U, M), select(M, U, U2), my_sort(U2, S2), append(S2, [M], S), !.
