%Elliott Dobbs
%CSCE 420
%Due: November 15, 2017
%hw3pr3.pl

mother(mum, elizabeth).
mother(mum, margaret).
mother(elizabeth, charles).
mother(elizabeth, anne).
mother(elizabeth, andrew).
mother(elizabeth, edward).
mother(kydd, diana).
mother(diana, william).
mother(diana, harry).
mother(anne, peter).
mother(anne, zara).
mother(sarah, beatrice).
mother(sarah, eugenie).
mother(sophie, louise).
mother(sophie, james).
mother(catherine, george2).
mother(catherine, charlotte).
mother(autumn, savannah).
mother(autumn, isla).
mother(zara, mia).

father(george, elizabeth).
father(george, margaret).
father(philip, charles).
father(philip, anne).
father(philip, andrew).
father(philip, edward).
father(spencer, diana).
father(charles, william).
father(charles, harry).
father(mark, peter).
father(mark, zara).
father(andrew, beatrice).
father(andrew, eugenie).
father(edward, louise).
father(edward, james).
father(william, george2).
father(william, charlotte).
father(peter, savannah).
father(peter, isla).
father(mike, mia).

spouse(george, mum).
spouse(elizabeth, philip).
spouse(spencer, kydd).
spouse(diana, charles).
spouse(anne, mark).
spouse(andrew, sarah).
spouse(edward, sophie).
spouse(william, catherine).
spouse(peter, autumn).
spouse(zara, mike).
spouse(mum, george).
spouse(philip, elizabeth).
spouse(kydd, spencer).
spouse(charles, diana).
spouse(mark, anne).
spouse(sarah, andrew).
spouse(sophie, edward).
spouse(catherine, william).
spouse(autumn, peter).
spouse(mike, zara).

male(george).
male(philip).
male(spencer).
male(charles).
male(mark).
male(andrew).
male(edward).
male(william).
male(harry).
male(peter).
male(james).
male(george2).

parent(X, Y) :- mother(X, Y).
parent(X, Y) :- father(X, Y).

grandchild(X, Y) :- mother(Y, M), mother(M, X).
grandchild(X, Y) :- mother(Y, M), father(M, X).
grandchild(X, Y) :- father(Y, M), mother(M, X).
grandchild(X, Y) :- father(Y, M), father(M, X).

cousin(X, Y) :- grandchild(X, G), grandchild(Y, G), male(G), mother(M, X), mother(M2, Y), M\==M2.

brother_in_law(X, Y) :- male(X), spouse(Y, S), mother(M, S), mother(M, X).

ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(X2, Y), parent(X, X2).
ancestor(X, Y) :- parent(X2, Y), parent(X3, X2), parent(X, X3).
ancestor(X, Y) :- parent(X2, Y), parent(X3, X2), parent(X4, X3), parent(X, X4).

