#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 2.57 ze str. 116
# ponizej wstawic te funkcje, zmienic im nazwy na f(x), g(x), h(x,a,b), itd
# zeby mogly byc w jednym pliku, naprawic je, wywolac, i skomentowac jaki byl blad

def f(x):    # colon
    return 1+x**2;

def g(x):
    term1 = 1
    term2 = x**2
    return term1 + term2;

def h(x,a,b):
    return a+b*x
print (h(1, 2, 3)) #incorrect entry

def j(x, w):
    from math import sin
    return sin(w*x)

w = 10      #change place of variables
x = 0.1
j = j(x, w) # with quotation marks output be only list of char
print j       #'str' object is not callable

from math import *
def log(message):
    print message

print ('The logarithm of 1 is', log(1))# need bracket for right output

import time
def print_CPU_time():
    print ("CPU time so far in the program:", time.clock()) # quotation marks
    
print_CPU_time() #brackets




