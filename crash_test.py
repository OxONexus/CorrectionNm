#!/bin/python
import sys
import os
import numpy as np
import random
from subprocess import Popen, PIPE


if __name__ == "__main__":
    f = open("ft_nm", "r");
    a = np.fromfile(f, dtype=np.uint32)
    while 1:
        b = np.insert(a,  random.randint(0, len(a)),  random.randint(0, 0xffffffff))
        b.tofile('.currtest')
        proc = Popen('./ft_nm .currtest', shell=True, stdout=PIPE, stderr=PIPE)
        out, err = proc.communicate()
        if proc.returncode == -11:
            break;

