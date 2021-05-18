#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 2.56 ze str. 115

x = 2.5

from math import exp, sin

def expsin(x, p, q):
    return exp(p*x)*sin(q*x)

def f(x, m, n, r, s):
    return expsin(x, r, m) + expsin(x, s, n)

print f(x, 0.1, 0.2, 1, 1)
