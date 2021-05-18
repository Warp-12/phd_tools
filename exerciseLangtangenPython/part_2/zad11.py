#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 3.23 ze str. 164
global str
import sys
from math import *
def equal(expr1, expr2, A, B, n=500):
	import random
	fc = n
	for i in range(n):
		a = random.uniform(A,B)
		b = random.uniform(A,B)
		if eval(expr1) == eval(expr2):
		    fc -= 1
	return float(fc)/ n * 100

if __name__ == '__main__':
    expr1 = sys.argv[1]
    expr2 = sys.argv[2]
    A = float(sys.argv[3])
    B = float(sys.argv[4])
    n = int(sys.argv[5])
    var = equal(expr1, expr2, A, B, n)
    print '%s failure percent ' % (var)
