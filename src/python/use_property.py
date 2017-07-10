#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Student(object):
  @property
  def score(self):
    return self._score

  @score.setter
  def score(self, value):
    if not isinstance(value, int):
      raise ValueError('score must be an integer!')
    if value < 0 or value > 100:
      raise ValueError('score must between 0~100')
    self._score = value

s = Student()
s.score = 60
print('s.score =', s.score)


class Screen(object):
  @property
  def width(self):
    return self._width

  @property
  def height(self):
    return self._height

  @width.setter
  def width(self, value):
    if isinstance(value, int) & (value > 0):
      self._width = value
    else:
      raise ValueError('width error')

  @height.setter
  def height(self, value):
    if isinstance(value, int) & (value > 0):
      self._height = value
    else:
      raise ValueError('height error')

  @property
  def resolution(self):
    return self._width * self._height

sc = Screen()
sc.width = 1024
sc.height = 768
print(sc.resolution)
assert sc.resolution == 786432, '1024 * 768 = %d?' % sc.resolution

