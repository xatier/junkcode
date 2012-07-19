likes(a, cpp).
likes(b, python).
likes(c, python).

friend(X, Y) :- \+(X = Y), likes(X, Z), likes(Y, Z).
python_hacker(X) :- likes(X, python).
