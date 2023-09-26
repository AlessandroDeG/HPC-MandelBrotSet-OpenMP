from logging import log
from matplotlib.cbook import ls_mapper
import matplotlib.pyplot as plt
#from mpl_toolkits import mplot3d
import pandas as pd
import numpy as np
import math


# Load data
colnames = ['nThreads', 'times']
data = pd.read_csv('resultsHistParallel.csv',names=colnames,index_col=False,sep=";")

nThreads = data['nThreads'].tolist()
times = data['times'].tolist()


plt.plot(nThreads, times,c='blue')
plt.scatter(nThreads, times, s=50, c='blue',alpha=0.5)

plt.xlabel('nThreads')
plt.ylabel('time')
plt.show()

times=[math.log(x,10) for x in times]

plt.plot(nThreads, times,c='blue')
plt.scatter(nThreads, times, s=50, c='blue',alpha=0.5)

plt.xlabel('nThreads')
plt.ylabel('time(log10)')
plt.show()


############

# Load data
colnames = ['nThreads', 'times']
data = pd.read_csv('resultsHistParallel2.csv',names=colnames,index_col=False,sep=";")

nThreads = data['nThreads'].tolist()
times = data['times'].tolist()


plt.plot(nThreads, times,c='blue')
plt.scatter(nThreads, times, s=50, c='blue',alpha=0.5)

plt.xlabel('nThreads')
plt.ylabel('time')
plt.show()

times=[math.log(x,10) for x in times]
nThreads=[math.log(x,2) for x in nThreads]

plt.plot(nThreads, times,c='blue')
plt.scatter(nThreads, times, s=50, c='blue',alpha=0.5)

plt.xlabel('Powers of 2 - nThreads(log2)')
plt.ylabel('time(log10)')
plt.show()






