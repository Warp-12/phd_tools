#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 3.3 ze str. 161
import sys                                                                                                    
                                                                                                              
try:                                                                                                          
      F = float(sys.argv[1])                                                                                
      C = (5.0/9) * (F - 32)                                                                                
      print '%.1f F = %.1f C' % (F, C)                                                                      
except IndexError:                                                                                            
        raise IndexError('ERROR: Doesnt input value!!!')    
