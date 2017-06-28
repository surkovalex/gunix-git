#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def sum1(start, end):
	total = 0
	for x in range(start, end+1):
		total += x
	return total

print('sum1(1, 10) = %d' % sum1(1, 10))

def sum2(start, end):
	total = 0
	for x in range(start, end+1):
		total += x**2 + 1
	return total

print('sum2(1, 10) = %d' % sum2(1, 10))

def sum(start, end, handle):
	total = 0
	for x in range(start, end+1):
		total += handle(x)
	return total

def identify(n):
	return n

print('sum(1, 100, identify) = %d' % sum(1, 100, identify))

def square_plus_one(n):
	return n**2 + 1

print('sum(1, 100, square_plus_one) = %d' % sum(1, 100, square_plus_one))

def cube(n):
	return n**3

print('sum(1, 100, cube) = %d' % sum(1, 100, cube))

def is_prime(n):
	def smallest_divisor(n):
		return find_divisor(n, 2)
	def find_divisor(n, test_divisor):
		if pow(test_divisor, 2) > n:
			return n
		elif n % test_divisor == 0:
			return test_divisor
		else:
			return find_divisor(n, test_divisor + 1)
	
	if 1 == n:
		return 0
	elif smallest_divisor(n) == n:
		return n
	else:
		return 0

print('sum(1, 100, is_prime) = %d' % sum(1, 100, is_prime))



