from pandas import Series, DataFrame
import datetime
import numpy as np
import pandas as pd
import pandas_datareader.data as web
import matplotlib.pyplot as plt

start = datetime.datetime(2016, 1, 1)
end = datetime.date.today()
baba = web.DataReader('BABA', 'yahoo', start, end)
print(baba.tail())

plt.plot(baba.index, baba['Open'])
plt.show()

