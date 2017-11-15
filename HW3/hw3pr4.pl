%Elliott Dobbs
%CSCE 420
%Due: November 15, 2017
%hw3pr4.pl

father(me, f).
father(s1, me).
father(d, me).
father(f, me).

mother(d, w).
mother(s1, w).
mother(me, d).
mother(s2, d).

spouse(me, w).
spouse(w, me).
spouse(f, d).
spouse(d, f).

male(me).
male(f).
male(s1).
male(s2).

child(X, Y) :- father(X, Y).
child(X, Y) :- mother(X, Y).

grandpa(Z, X) :- male(Z), child(Y, Z), child(X, Y).





