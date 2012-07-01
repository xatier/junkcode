#!/usr/bin/env python

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


if __name__ == '__main__' :
    table = [] 
    gen (table)
    for i in table :
        print "%d, " % i,
