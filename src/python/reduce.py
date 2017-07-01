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





