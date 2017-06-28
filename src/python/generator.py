#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def fab(max):
  n, a, b = 0, 0, 1
  while n < max:
    print(b)
    a, b = b, a+b
    n = n+1
  return 'done'
fab(6)

def fab1(max):
  n, a, b = 0, 0, 1
  while n < max:
    yield b
    a, b = b, a+b
    n = n+1
  return 'done'
for n in fab1(6):
	print(n)

g = fab1(6)
while True:
	try:
		x = next(g)
		print('g:', x)
	except StopIteration as e:
		print('Generation return value:', e.value)
		break

def odd():
  print('step 1')
  yield 1
  print('step 2')
  yield 3
  print('step 3')
  yield 5
for n in odd():
	print(n)

def triangles():
  L = [1]
  while True:
    yield L
    L = [1] + [ L[x-1] + L[x] for x in range(1, len(L)) ] + [1]
n = 0
for t in triangles():
	print(t)
	n = n+1
	if n == 10:
		break

def triangles1():
	line = [1]
	while True:
		yield line
		line = [x+y for x, y in zip([0]+line, line+[0])]
n = 0
for t in triangles1():
	print(t)
	n = n+1
	if n == 10:
		break


