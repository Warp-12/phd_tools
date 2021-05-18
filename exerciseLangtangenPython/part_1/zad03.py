#!/usr/bin/python
# -*- coding: utf-8 -*-

# Zrobic zadanie 2.35 ze str. 107
def kinematics(x, y, t, dt = 1E-6):
      vx = (x(t+dt)-x(t-dt))/(2.0*dt)                     
      vy = (y(t+dt)-y(t-dt))/(2.0*dt)    
      ax = (x(t+dt)-2*x(t)+x(t-dt))/float(dt**2)
      ay = (y(t+dt)-2*y(t)+y(t-dt))/float(dt**2)  
      posx = x(t)
      posy = y(t)

      return (posx,posy), (vx,vy), (ax,ay)


from math import cos, pi, sin
R = 1
w = 2*pi
x = lambda t: R*cos(w*t)
y = lambda t: R*sin(w*t)
(posx, posy), (vx,vy), (ax,ay) = kinematics(x, y, t = 1, dt = 1E-5)
print ('''For the functions x = Rcos(wt), y = Rsin(wt) :
x(t) = %f
y(t) = %f
v(x(t)) = %f
v(y(t)) = %f 
a(x(t)) = %f
a(y(t)) = %f''' % (posx, posy, vx, vy, ax, ay))
