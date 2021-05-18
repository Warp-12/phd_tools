#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 2.13 ze str. 101
# oprocz programu w komentarzach napisac odpowiedzi na pytania w zadaniu


# This program calculated the amount of years
# it takes for an amount of money to reach 1.5
# times its value, given and interest rate of p

#To solve the integer division error if p is an 
#int, it was necessary to change p/100 to p/100.

p = 5.5 #interst rate

while True:
        initial_amount =  int(input('Write initial amount: '))
        years =  int(input ('Write init year: '))
        amount = initial_amount
        amount +=  p/100.*initial_amount
        years += 1
        print (years , amount)
        
