#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def fab(max):
  n, a, b = 0, 0, 1
  while n < max:
    print(b)
    a, b = b, a+b
    n = n+1
  return 'done'

def fab1(max):
  n, a, b = 0, 0, 1
  while n < max:
    yield b
    a, b = b, a+b
    n = n+1
  return 'done'

def odd():
  print('step 1')
  yield 1
  print('step 2')
  yield 3
  print('step 3')
  yield 5

def triangles():
  L = [1]
  while True:
    yield L
    L = [1] + [ L[x-1] + L[x] for x in range(1, len(L)) ] + [1]






