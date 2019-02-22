:- module(hw5: [configuration/3]).
:- [hardware].

isinner(X):-
adjacent(X,Y),adjacent(X,Z),\+ (Y = Z), adjacent(A,X),adjacent(B,X), \+ (A = B).

isouther(X):-
sections(S),
insection(X,S),
\+ isinner(X).


isinCS(A,[],notin(A)):-!.
isinCS(A,[outer_edge(A)|_],outer_edge(A)):-!.
isinCS(A,[close_to(A,B)|_],close_to(A,B)):-!.
isinCS(A,[close_to(B,A)|_],close_to(B,A)):-!.
isinCS(A,[_|Bl],C):-
isinCS(A,Bl,C).


isinformer(_,[],0):-!.
isinformer(X,[put(_,X1)|A],R):-
(X == X1,
 R is 1,!
);
(\+(X = X1),isinformer(X,A,R)).

isinformer2(_,[],0):-!.
isinformer2(X,[put(X1,_)|A],R):-
(X == X1,
 R is 1,!
);
(\+(X = X1),isinformer2(X,A,R)).


insection(C,[C]):-!.
insection(C,[C|_]).
insection(C,[_|Cs]):-
insection(C,Cs).





findplace(X,[put(X,R)|_],R):-!.
findplace(X,[_|Pl],R):-
findplace(X,Pl,R).


appendl([],L,L).
appendl([H|T],L,[H|Z]):-
appendl(T,L,Z).





configuration2([],_,[],_):-!.
configuration2([A|Al],B,[put(A, C)|Cl],F):-
(
isinCS(A,B,Oe),
Oe == outer_edge(A),
isouther(C),
isinformer(C,F,0),
configuration2(Al,B,Cl,[put(A,C)|F])
);
(
isinCS(A,B,close_to(A,S)),
isinformer2(S,F,0),
sections(X),
insection(C,X),
isinformer(C,F,0),
configuration2(Al,B,Cl,[put(A,C)|F])
);
(
isinCS(A,B,close_to(S,A)),
isinformer2(S,F,1),
sections(X),
insection(C,X),
isinformer(C,F,0),
findplace(S,F,R),
(adjacent(C,R);adjacent(R,C)),
configuration2(Al,B,Cl,[put(A,C)|F])
);
(
isinCS(A,B,close_to(A,S)),
isinformer2(S,F,1),
sections(X),
insection(C,X),
isinformer(C,F,0),
findplace(S,F,R),
(adjacent(C,R);adjacent(R,C)),
configuration2(Al,B,Cl,[put(A,C)|F])
);
(
isinCS(A,B,close_to(S,A)),
isinformer2(S,F,0),
sections(X),
insection(C,X),
isinformer(C,F,0),
configuration2(Al,B,Cl,[put(A,C)|F])
);
(
isinCS(A,B,Ni),
Ni == notin(A),
sections(X),
insection(C,X),
isinformer(C,F,0),
configuration2(Al,B,Cl,[put(A,C)|F])
).




configuration([],_,[]).
configuration([A|Al],B,[C|Cl]):-
configuration2([A|Al],B,[C|Cl],[]).
