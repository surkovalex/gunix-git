#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Fib(object):
	def __init__(self):
		self.a, self.b = 0, 1

	def __iter__(self):
		return self

	def __next__(self):
		self.a, self.b = self.b, self.a + self.b
		if self.a > 100000:
			raise StopIteration()
		return self.a

	def __getitem__(self, n):
		a, b = 1, 1
		if isinstance(n, int):		# n is index
			for x in range(n):
				a, b = b, a+b
			return a
		if isinstance(n, slice):	# n is slice
			start = n.start
			stop = n.stop
			step = n.step
			if start is None:
				start = 0
			if step is None:
				step = 1
			L = []
			for x in range(stop):
				if x >= start and (x - start) % step == 0:
					L.append(a)
				a, b = b, a+b
			return L

f = Fib()
print(f[0])
print(f[5])
print(f[100])
print(f[0:5])
print(f[:10])
print(f[1:10:2])

