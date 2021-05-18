#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 2.30 ze str. 105

def integrate(f, a, b):
        lim1 = f(a)
        lim2 = f(b)
        h = b - a
        area = 1./2*h*(lim1 + lim2)
        return area
      
from math import exp, cos, sin, pi, log
f = [lambda x: exp(x), lambda x: cos(x), lambda x:  sin(x), lambda x:  sin(x)]
F = [lambda x: exp(x), lambda x: sin(x), lambda x: -cos(x), lambda x: -cos(x)]
s = ['exp(x)', 'cos(x)', 'sin(x)', 'sin(x)']
limits = [[0, log(3)], [0, pi], [0, pi], [0, pi/2]]
print ('%10s, %15s, %15s' % ('function', 'limits', 'error'))
for i in range(4):
      exact =  F[i](limits[i][1]) - F[i](limits[i][0])
      approach = integrate(f[i], limits[i][0], limits[i][1])
      error = abs(exact - approach)
      print ('%10s %10f to %10f %11g' % (s[i], limits[i][0], limits[i][1], error))

