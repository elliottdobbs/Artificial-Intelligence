%Elliott Dobbs
%CSCE 420
%Due: November 15, 2017
%my_max.pl as given in class
          
my_max([], -2147483648).
my_max([X], X).
my_max(L , X) :- member(X, L), forall(member(Y, L), X >= Y).
