#!/usr/bin/env python3

# -*- coding:utf-8 -*-

import re
from datetime import datetime, timezone, timedelta

def to_timestamp(dt_str, tz_str):
  dt = datetime.strptime(dt_str, '%Y-%m-%d %H:%M:%S')
  tz_info = re.split(r'[UTC\:]+',tz_str)
  tz_hours = int(tz_info[1])
  tz_minutes = int(tz_info[2])
  dt = dt.replace(tzinfo = timezone(timedelta(hours=tz_hours, minutes=tz_minutes)))
  return dt.timestamp()

t1 = to_timestamp('2015-6-1 08:10:30', 'UTC+7:00')
assert t1 == 1433121030.0, t1
print(t1)

t2 = to_timestamp('2015-5-31 16:10:30', 'UTC-09:00')
assert t2 == 1433121030.0, t2
print(t2)

print('Pass')

