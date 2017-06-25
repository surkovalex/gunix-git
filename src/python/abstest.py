#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

def quadratic(a, b, c):
  if b**2 - 4*a*c > 0:
    x1 = (-b + math.sqrt(b**2 - 4*a*c))/(2*a)
    x2 = (-b - math.sqrt(b**2 - 4*a*c))/(2*a)
    return x1, x2
  elif b**2 - 4*a*c == 0:
    return -b/(2*a)
  else:
    return 'unslovable'

print(quadratic(2, 3, 1))
print(quadratic(1, 3, -4))

def move(x, y, step, angle = 0):
  nx = x + step*math.cos(angle)
  ny = y + step*math.sin(angle)
  return nx, ny

def my_abs(x):
  if not isinstance(x, (int, float)):
    raise TypeError("bad operand type")
  if x >= 0:
    return x
  else:
    return -x

