#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
from math import sqrt

def get_result(a, b, *fns):
	return [fn(a+b) for fn in fns]

a = 3
b = 4
print('result:', get_result(a, b, abs, math.ceil, math.floor))

def same(x, *fs):
	return [f(x) for f in fs]

print(same(2, sqrt, abs))

def do_sth(x=[], *func):
	return [f(x_k) for x_k in x for f in func]

print(do_sth([1, 2, 4, 9], abs, sqrt))



