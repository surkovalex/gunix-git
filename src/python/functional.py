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

def product(start, end, handle):
	total = 1;
	for x in range(start, end+1):
		total *= handle(x)
	return total

def factroial(n):
	return product(1, n, identify)

print('product(1, 10, identify) = %d' % factroial(10))

def accumulate(start, end, handle, init_value, combine):
	def symbol(a, b, combine):
		if '+' == combine:
			return a+b
		elif '*' == combine:
			return a*b
		else:
			pass

	total = init_value
	for x in range(start, end+1):
		total = symbol(total, handle(x), combine)
	return total

def sum(start, end, handle):
	return accumulate(start, end, handle, 0, '+')

def product(start, end, handle):
	return accumulate(start, end, handle, 1, '*')

print('sum(1, 100, identify) = %d' % sum(1, 100, identify))
print('product(1, 6, identify) = %d' % product(1, 6, identify))


def Sum(start, end, handle):
	return reduce(lambda x, y: x + y, map(lambda x: handle(x), \
			[x for x in range(start, end + 1)]))

def Product(start, end, handle):
	return reduce(lambda x, y: x * y, map(lambda x: handle(x), \
			[x for x in range(start, end + 1)]))

def Accumulate(start, end, handle, combine):
	def symbol(a, b, combine):
		if '+' == combine:
			return a+b
		elif '*' == combine:
			return a*b
		else:
			pass

	return reduce(lambda x, y: symbol(x, y, combine), map(lambda x: handle(x), \
			[x for x in range(start, end + 1)]))

def Sum(start, end, handle):
	return accumulate(start, end, handle, '+')

def Product(start, end, handle):
	return accumulate(start, end, handle, '*')


