#!/usr/bin/env python

import sys

def gen (table) : 
    tmp = {}
    N = 1000000
    for i in range (0, N) :
        tmp[i] = 1

    for i in range (2, N) :
        if tmp[i]  == 1 :
            for j in range (2, N/i) :
                tmp[i*j] = 0

    for i in range (2, N) :
        if tmp[i] == 1 :
            table.append(i)

    print "done"


def factorization(n):
    sys.stdout.write ("Prime factorization of %d = " % (n))
    (i, N, S) = (0, 1, 1)
    while n > 1:
        p = table[i]
        e = 0
        while n % p == 0 :
            e += 1
            n /= p
        if e > 0:
            sys.stdout.write ("pow(%d,%d)" % (p, e))
            N *= e + 1
            ss = sum(p**t for t in range(e+1))
            S *= ss 

        i += 1

    sys.stdout.write ("\nNumber of divisors = %d\nSum of divisors = %d\n\n" % (N, S))
    

if __name__ == '__main__' :

    table = []
    gen(table)

    while 1 :
        try :
            n = int (raw_input ("Enter an integer >= 2: "))
            factorization (n)
        except EOFError :
            break
