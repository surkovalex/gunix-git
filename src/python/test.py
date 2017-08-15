import pandas as pd
import pandas_datareader.data as web
import matplotlib.pyplot as plt
import datetime

start = datetime.datetime(2017, 1, 1)
end = datetime.date.today()

maotai = web.DataReader('600519.ss', 'yahoo', start, end)

type(maotai)
len(maotai)

maotai.head()
maotai.tail()

%matplotlib inline
%pylab inline

