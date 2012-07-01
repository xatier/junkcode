#!/usr/bin/env python

import sys

def good (n) :
    s = str (n)
    l = len (s) - 2
    L = []

    if l <= 0 :
         L.append(s)

    for i in range (0, l) :
        L.append (s[i:i+3])

    L.sort()

    for i in range (1, len(L)) :
        if L[i] == L[i-1] :
            return 0
    return 1


def bad (n) :
    if (str(n).find('1') == -1 or 
        str(n).find('3') == -1 or
        str(n).find('5') == -1) :
        return 0     
    else :
        return 1 

def ugly (n) :
    while n % 2 == 0 :
        n /= 2
    while n % 3 == 0 :
        n /= 3
    while n % 5 == 0 :
        n /= 5
    return n == 1

if __name__ == '__main__' :
    while 1 :
        try :
            n = int (raw_input ("Enter an unsigned integer >= 1: "))
            sys.stdout.write ("%s"   % ("Good, " if good (n) else "Not good, "))
            sys.stdout.write ("%s"   % ("Bad, "  if bad (n)  else "Not bad, "))
            sys.stdout.write ("%s\n" % ("Ugly"   if ugly (n) else "Not ugly"))
        except EOFError :
                break
