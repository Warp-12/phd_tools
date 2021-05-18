#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 3.15 ze str. 163
# program niech sie nazwya zad06.py, a modul niech sie nazwya zad06_module.py
# to samo nazewnictwo uzywac w kolejnych zadaniach
# nie duplikowac modulow. Tzn zad0m.py moze importowac zad0n_module.py
import zad06_module
print 'Converts C %g F'  % (zad06_module.C2F(20))
print 'Converts F %g C'  % (zad06_module.F2C(20))
print 'Converts C %g K'  % (zad06_module.C2K(20))
print 'Converts K %g C'  % (zad06_module.K2C(20))
print 'Converts F %g K'  % (zad06_module.F2K(20))
print 'Converts K %g F'  % (zad06_module.K2F(20))

