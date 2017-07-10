#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import functools

def logger(text):
  def decorator(func):
    @functools.wraps(func)
    def wrapper(*args, **kw):
      print('begin %s %s' % (text, func.__name__))
      fun = func(*args, **kw)
      print('end %s %s' % (text, func.__name__))
      return fun
    return wrapper
  return decorator

@logger('test')
def now():
  print('2017-07-05')

now()


def logger2(unknow):
	def decorator(func):
		@functools.wraps(func)
		def wrapper(*arg, **kw):
			if not isinstance(unknow, str):
				text="call"
			else:
				text=unknow
			print("begin call")
			print("%s %s():" % (text,func.__name__))
			func(*arg, **kw)
			print("end call")
			return
		return wrapper
	if isinstance(unknow, str):
		return decorator
	else:
		return decorator(unknow)

#@logger2
@logger2("exec")
def now2():
	print('2017-07-06')

now2()


def logger3(text):
	def decorator(func):
		@functools.wraps(func)
		def wrapper(*args, **kw):
			if isinstance(text, (int, str)):
				print('%s, %s():' % (text, func.__name__))
			else:
				print('call %s():' % func.__name__)
			return func(*args, **kw)
		return wrapper
	if isinstance(text, (int, str)):
		return decorator
	else:
		return decorator(text)

@logger3('test')
def now3():
	print('2017-07-06')

now3()

