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


