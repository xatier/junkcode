#!/usr/bin/env python

import sys

stack = []

def show (n) :
    if n == 0 :
        return
    show (n - 1)
    sys.stdout.write ("%d " % stack[n - 1])


def q (n, k) :
    if n < 0 or k == 0:
        return 0
    elif n == 0 :
        show (len (stack))
        sys.stdout.write ("\n")
        return 1
    else :
        stack.append(k)
        a = q (n-k, k)
        stack.pop()
        return a + q (n, k-1)


def ui ():
    try :
        n = int (raw_input ("Enter a positive integer <= 20: "))
        sys.stdout.write ("There are %d ways to partition %d.\n" % (q (n, n), n))
        ui()
    except EOFError :
        return


if __name__ == '__main__' :
    ui() 
