#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 3.22 ze str. 164
import random
import sys
A = -100
B = 100
var = float(sys.argv[1])
eps = 1E-10
fc1 = 0
fc2 = 0

for i in range(int(var)):
    a = random.uniform(A,B)
    b = random.uniform(A,B)
    if abs((a*b)**3 - a**3*b**3) >= eps:
        fc1 += 1
    if abs(a/b - 1/(b/a)) >= eps:
        fc2 +=1
print '(a*b)**3 == a**3*b**3 %.1f failure percent' % ((1-float(fc1)/var)*100)
print 'a/b == 1/(b/a)        %.1f failure percent' % ((1-float(fc2)/var)*100)
