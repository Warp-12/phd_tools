#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 3.1 ze str. 160


F = eval(raw_input('Enter temperature in Fahrenheit: '))
C = (F - 32.0)*5.0/9
print '%.1f F = %.1f C' % (F, C)
