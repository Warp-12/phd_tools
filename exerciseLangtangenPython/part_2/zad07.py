#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 3.16 ze str. 163
if __name__ == '__main__':
        import zad06_module
        import sys
	use = '%s x scale\nx is a real number, scale is F, C, or K' \
	       % sys.argv[0]
	try:
		x = eval(sys.argv[1])
		scale = sys.argv[2]
	except:
		print use
		sys.exit(1)
	if scale == 'C':
		print '%.2f %s %.2f %s' % (zad06_module.C2F(x), 'F', zad06_module.C2K(x), 'K')
	elif scale == 'F':
		print '%.2f %s %.2f %s' % (zad06_module.F2C(x), 'C', zad06_module.F2K(x), 'K')
	elif scale == 'K':
		print '%.2f %s %.2f %s' % (zad06_module.K2F(x), 'F', zad06_module.K2C(x), 'C')
	else:
                raise ValueError('scale must be F, C, or K')
