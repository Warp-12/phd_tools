#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 2.60 ze str. 117
numbers = range(10) #declaration a list of 10 integers
print numbers # prints numbers
for n in numbers:
        i = len(numbers)/2
        del numbers[i]
        print 'n=%d, del %d' % (n,i), numbers
# In each step in for loop are deleted one of number from list,
        number to be deleted is choose by division of conteiner length by 2
