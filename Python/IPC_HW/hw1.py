#!/usr/bin/env python

import sys

def gen (n) :

    (x0 , x1, y0, y1, count) = (0, 1, 1, n, 2)
    (x2 , y2)= (((y0 + n) / y1) * x1 - x0, ((y0 + n) / y1) * y1 - y0)
    sys.stdout.write ("%d/%d %d/%d " % (x0, y0, x1, y1))

    while x1 != y1 :
        (x0, y0) = (x1, y1)
        (x1, y1) = (x2, y2)
        (x2 , y2)= (((y0 + n) / y1) * x1 - x0, ((y0 + n) / y1) * y1 - y0)
        sys.stdout.write ("%d/%d " % (x1, y1))
        count += 1

    sys.stdout.write ("\nThe Farey sequence of order %d has %d terms.\n\n" % (n, count))

if __name__ == '__main__' :
    while 1 :
        try :
            n = int(raw_input("Enter an integer >= 1: "))
            gen(n)
        except EOFError :
            break
