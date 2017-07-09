#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class FooClass(object):
  """my very first class: FooClass"""
  version = 0.1     # class (data) attribute

  def __init__(self, nm='John Doe'):
    """constructor"""
    self.name = nm    # class instance (data) attribute
    print('Create a class instance for', nm)

  def showname(self):
    """display instance attribute and class name"""
    print('Your name is', self.name)
    print('My nmae is', self.__class__.__name__)

  def showver(self):
    """display class(static) attribute"""
    print(self.version)    # reference FooClass.version

  def addMe2Me(self, x):
    """apply + operation to argument"""
    return x + x

foo = FooClass()
foo.showname()
foo.showver()
print(foo.addMe2Me(5))
print(foo.addMe2Me('xyz'))

foo2 = FooClass('Jane Smith')
foo2.showname()

