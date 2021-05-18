#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 3.11 ze str. 162
import calendar
import sys
age = '%s Input date consisting of year (4 digits), month (2 digits), and day (1-31)' % sys.argv[0]
try:
    year = eval(sys.argv[1])
    month =  eval(sys.argv[2])
    day = eval(sys.argv[3])
except:
    print age
    sys.exit(1)
i = calendar.weekday(year,month,day)
weekdays = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday']
print 'On date %d/%d/%d is %s' % (day, month, year, weekdays[i])
