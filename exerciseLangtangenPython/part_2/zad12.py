#!/usr/bin/python
# -*- coding: utf-8 -*-

# zadanie TRUDNE ale KONIECZNE
# Zrobic zadanie 3.24 ze str. 165
# Uwaga - zastosowac remark podany na koniec zadania 3.24
#         jesli nie zostanie zrobiona automatyzacja tego procesu
#         zadania z calego tygodnia nie beda zaliczone.
from zad11 import equal
formuls = [
    ('a - b', '-(b - a)'),
    ('a/b', '1/(b/a)'),
    ('(a*b)**4', 'a**4*b**4'),
    ('(a + b)**2', '(a**2 + 2*a*b + b**2)'),
    ('(a + b)*(a - b)', 'a**2 - b**2'),
    ('exp(a + b)', 'exp(a)*exp(b)'),
    ('log(a**b)', 'b*log(a)'),
    ('log(a*b)', 'log(a) + log(b)'),
    ('a*b', 'exp(log(a) + log(b))'),
    ('1/(1/a + 1/b)', 'a*b/(a + b)'),
    ('a*(sin(b)**2 + cos(b)**2)', 'a'),
    ('sinh(a + b)', '0.5*(exp(a)*exp(b) - exp(-a)*exp(-b))'),
    ('tan(a + b)', 'sin(a + b)/cos(a + b)'),
    ('sin(a + b)', 'sin(a)*cos(b) + sin(b)*cos(a)')
]

A = 1
B = 50

print '%55s %20s' % ('Mathematical expressions', 'Failure ')
for i in xrange(len(formuls)):
    failure = equal(formuls[i][0], formuls[i][1], A, B)
    math_exp = formuls[i][0] + ' and ' + formuls[i][1]
    print '%55s %20g%%' % (math_exp, failure)
