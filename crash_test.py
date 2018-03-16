#!/bin/python
import sys
import os
import numpy as np
import random
from subprocess import Popen, PIPE
from time import sleep



if __name__ == "__main__":
    f = open(sys.argv[1], "r");
    a = np.fromfile(f, dtype=np.uint32)
    test = 0;
    while 1:
        rd = random.randint(0, 3)
        if rd == 0:
            b = np.delete(a,  random.randint(0, len(a) - 1), 0)
        elif rd == 1:
            a[random.randint(0, len(a) - 1)] = random.randint(0, 0xffffffff)
            b = a;
        elif rd == 2:
            b = a[random.randint(0, len(a) - 1):]
        else:
            b = np.insert(a,  random.randint(0, len(a)),  random.randint(0, 0xffffffff))
        b.tofile('.currtest-'+str(test))
        if random.randint(0, 1) == 1:
            print "NM       Crash test:" + str(test)
            proc = Popen('./ft_nm .currtest-'+str(test), shell=True, stdout=PIPE, stderr=PIPE)
        else:
            print "OTOOL    Crash test:" + str(test)
            proc = Popen('./ft_otool .currtest-'+str(test), shell=True, stdout=PIPE, stderr=PIPE)
        proc.wait()
        if proc.returncode == -11:
            b.tofile('report_crash/' + sys.argv[1].replace('/', '-') + ":" +str(test))
            print "Crash:" + str(test)
        os.remove(".currtest-"+str(test))
        test += 1;

