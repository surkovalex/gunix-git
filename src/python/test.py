#!/usr/bin/env python3.5
# -*- coding: utf-8 -*-

def print_scores(**kw):
  print('   name    score')
  print('----------------')
  for name, score in kw.items():
    print('%10s,    %d' %(name, score))
  print()



