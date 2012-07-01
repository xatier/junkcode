#!/usr/bin/env python

import sys

def judge (n) :
    if n == '+' or n == '-' :
        return 0
    elif n == '.' :
        return 1
    elif '0' <= n <= '9' :
        return 2
    elif n == '\n' :
        return 3

def f (n) :
    q = 's'
    for i in range (0, len(n)) :
        j = judge (n[i:i+1])
        if q == 's' :
            q = ('s' if j == 0 else 'd' if j == 2 else 'f' if j == 1 else 'e')
        elif q == 'd' :
            q = ('d' if j == 2 else 'r' if j == 1 else 'e')
        elif q == 'f' :
            q = ('r' if j == 2 else 'e')
        elif q == 'r' :
            q = ('r' if j == 2 else 'e')


    return q == 'r'

if __name__ == '__main__' :
    while 1 :
        try :
            n = raw_input ('Enter a real constant: ')
            sys.stdout.write ("%s\n" % ("Accepted" if f (n) else "Rejected"))
        except EOFError :
            break

