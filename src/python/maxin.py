#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class father():
	def func(self):
		print('生父打儿子')

class laowang():
	def func(self):
		print('老王打儿子')
	def func1(self):
		print('跟你妈说我明天下午会来')

class stepfather():
	def func(self):
		print('继父打儿子')
	def func1(self):
		print('我还会打尼玛')

class mysterious(father, laowang, stepfather):
	pass

s = mysterious()
s.func()
s.func1()


