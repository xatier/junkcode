#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import sys
import os

while 1 :
    try :
        t = []
        t.append(int (time.localtime().tm_hour))
        t.append(int (time.localtime().tm_min))
        t.append(int (time.localtime().tm_sec))
        for i in range (3) :
            for j in range (8, -1, -1) :
                sys.stdout.write ("%s" % ("●" if (t[i] >> j & 1) else "  "))
            print
        time.sleep (1)
        os.system ('clear')
    except :
        print "\b\b廢物！竟敢中斷我！ "
        break
