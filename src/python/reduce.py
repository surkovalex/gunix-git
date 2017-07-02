#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from functools import reduce

def fn(x, y):
  return 10*x + y

def char2num(s):
  return {'0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9}[s]

def str2int(s):
  return reduce(fn, map(char2num, s))

print('str2int(\'32898\') = %d' % str2int('32898'))

def str2int2(s):
  return reduce(lambda x, y : 10*x+y, map(char2num, s))

print('str2int2(\'32898\') = %d' % str2int2('32898'))

CHAR_TO_INT = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9 }

def str2int3(s):
  ints = map(lambda ch: CHAR_TO_INT[ch], s)
  return reduce(lambda x, y: x * 10 + y, ints)

print(str2int('0'))
print(str2int('12300'))
print(str2int('0012345'))

CHAR_TO_FLOAT = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '.': -1}

def str2float(s):
  nums = map(lambda ch: CHAR_TO_FLOAT[ch], s)
  point = 0
  def to_float(f, n):
    nonlocal point
    if n == -1:
      point = 1
      return f
    if point == 0:
      return 10*f+n
    else:
      point = 10*point
      return f+n/point
  return reduce(to_float, nums, 0.0)

print(str2float('0'))
print(str2float('123.456'))
print(str2float('123.45600'))
print(str2float('0.1234'))
print(str2float('.1234'))
print(str2float('120.0034'))

def normalize(name):
  return name.capitalize()

L1 = ['adam', 'LISA', 'barT']
L2 = list(map(normalize, L1))
print(L2)

def prod(L):
  return reduce(lambda x, y : x*y, L)

print('3 * 5 * 7 * 9 =', prod([3, 5, 7, 9]))





