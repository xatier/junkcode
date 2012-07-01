#!/usr/bin/env python

import sys

def sum1 (n) :
    (sum, sign) = (n, 1)
    S = ['+', '-']
    sys.stdout.write ("%d" % (n))
    n /= 10
    while n > 0 :
        sys.stdout.write ("%c%d" % (S[sign], n))
        sum += n*(-1)**sign
        sign = 1 - sign
        n /= 10

    sys.stdout.write (" = %d\n" % (sum))

def sum2 (n) :
    (l, sum) = (len (str (n)) - 1, 0)
    while l >= 0 :
        sys.stdout.write ("%d+" % (n / (10**l)))
        sum += (n / (10**l))
        l -= 1

    sys.stdout.write ("\b = %d\n" % (sum))

def sum3 (n) :
    (l, sum) = (len (str (n)), 0)
    for i in range (1, l+1) :
        sys.stdout.write ("%0*d+" % (i, n % (10**i)))
        sum += (n % (10**i))

    sys.stdout.write ("\b = %d\n\n" % (sum))


if __name__ == '__main__' :
    while 1 : 
        try :
            n = int(raw_input ("Enter an integer >=0: ")) 
            sum1 (n)
            sum2 (n)
            sum3 (n)
        except EOFError :
            break
