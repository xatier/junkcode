#!/usr/bin/python
# -*- coding: utf-8 -*

import sys
import os
import time
import random

N = 25                                 # map length
direct = [                                                                    
    [-1, -1], [-1, 0], [-1, 1],
    [ 0, -1],          [ 0, 1],
    [ 1, -1], [ 1, 0], [ 1, 1]
  ]

m = {}                                 # current map
nm = {}                                # next map


def init () :                          # init the map
    for i in range (1, N+1) :
        for j in range (1, N+1) :
            m[i+j*N] = 0
            nm[i+j*N] = 0;
    m['color'] = 0;



def print_m () :
#    os.system('clear')                # i don't know others method to clear
                                       # the screen orz
    sys.stdout.write ("\033[2J")       # using VT100 cmd 
    for i in range (1, N+1) :
        for j in range (1, N+1) :
            cc = "\033[1;%d;40m" % (30+m['color'])
            if m[i+j*N] == 1 :
                sys.stdout.write ("%s0 \033[m" % (cc))
            elif m[i+j*N] == 0 :
                sys.stdout.write ("\033[0;37;40m. \033[m")
        print                          # new line

    m['color'] += 1                    # change to next color
    m['color'] %= 6



def update () :
    for i in range (1, N+1) :
        for j in range (1, N+1) :
            m[i+j*N] = nm[i+j*N]



def gen_next () :
    for i in range (1, N+1) :
        for j in range (1, N+1) :
            t = 0                      # t to count its neighbors
            for k in range (0, 8) :
                try :
                    t += m[(i+direct[k][0]) + (j+direct[k][1])*N]
                except :
                    pass               # maybe its neighbor is undefined Q_Q

            if m[i+j*N] == 1 :
                if t == 0 or t == 1 :
                    nm[i+j*N] = 0
                elif t >= 4 :
                    nm[i+j*N] = 0
                elif t == 2 or t == 3 :
                    nm[i+j*N] = 1
            elif m[i+j*N] == 0 :
               if t == 3 :
                    nm[i+j*N] = 1 

def go () :
    while 1 :
        try :
            ss = raw_input()
            if ss == 'r':
                rnd ()
        except EOFError :
            print ('哭哭喔~')
            break
        
        tt = 50
        while tt > 0 :
            try :
                gen_next ()
                print_m ()
                update ()
                time.sleep(0.3)
            except KeyboardInterrupt :
                print ('廢物！竟敢中斷我！')
                return                       # pretend nothing happend XD
    

def rnd () :
    T = 80
    while T > 0 :
        try :
            nm[(random.randint(0,N))+(random.randint(0,N))*N] ^= 1
        except :
            pass
        T -= 1
    update ()

if __name__ == '__main__' :
    
    init ()
    # a simple example
    m[3+2*N] = m[1+3*N] = m[3+3*N] = m[2+4*N] = m[3+4*N] = 1;
    print_m ()
    try :
        go ()
    except KeyboardInterrupt :
        print ('廢物！竟敢中斷我！')

