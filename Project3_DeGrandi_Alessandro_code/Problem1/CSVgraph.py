from logging import log
from matplotlib.cbook import ls_mapper
import matplotlib.pyplot as plt
#from mpl_toolkits import mplot3d
import pandas as pd
import numpy as np
import math


# Load data
colnames = ['nThreads', 'sizes','serial','reduction','critical']
data = pd.read_csv('results.csv',names=colnames,index_col=False,sep=";")

nThreads = data['nThreads'].tolist()
size = data["sizes"].tolist()
serial = data["serial"].tolist()
reduction = data["reduction"].tolist()
critical = data["critical"].tolist()

#print(nThreads)
#print(size)
#print(serial)
#print(reduction)
#print(critical)



#print(len(size))
#print(size)
#print(len(serial))
#print(len(reduction))
#print(len(critical))

digits=[]

digits20=[]
serial20=[]
reduction20 =[]
critical20=[]

digits10=[]
serial10=[]
reduction10 =[]
critical10=[]

digits2=[]
serial2=[]
reduction2=[]
critical2=[]


serialS5=[]
reductionS5=[]
criticalS5=[]
nThreadsS5 = []
serialS6=[]
reductionS6=[]
criticalS6=[]
nThreadsS6 = []
serialS7=[]
reductionS7=[]
criticalS7=[]
nThreadsS7 = []
serialS8=[]
reductionS8=[]
criticalS8=[]
nThreadsS8 = []
serialS9=[]
reductionS9=[]
criticalS9=[]
nThreadsS9 = []



index=0
for n in size:
    reduction[index]=math.log(reduction[index],10)
    critical[index]=math.log(critical[index],10)
    serial[index]=math.log(serial[index],10)
    digits.append(int(round(math.log(size[index],10))))

                
    index+=1
        
#print(index)
index=0
for n in nThreads:

    if(n == 20):
        digits20.append(digits[index])
        serial20.append(serial[index])
        reduction20.append(reduction[index])
        critical20.append(critical[index])
    if(n == 10):
        digits10.append(digits[index])
        serial10.append(serial[index])
        reduction10.append(reduction[index])
        critical10.append(critical[index])

    if(n == 2):
        digits2.append(digits[index])
        serial2.append(serial[index])
        reduction2.append(reduction[index])
        critical2.append(critical[index])
    index+=1

#fixed times for loop plotting
index=0
for n in digits:

        if(n==5):
    
            serialS5.append(serial[index])
            reductionS5.append(reduction[index])
            criticalS5.append(critical[index])
            nThreadsS5.append(nThreads[index])
        
        if(n==6):
    
            serialS6.append(serial[index])
            reductionS6.append(reduction[index])
            criticalS6.append(critical[index])
            nThreadsS6.append(nThreads[index])
        if(n==7):

            serialS7.append(serial[index])
            reductionS7.append(reduction[index])
            criticalS7.append(critical[index])
            nThreadsS7.append(nThreads[index])

        if(n==8):

            serialS8.append(serial[index])
            reductionS8.append(reduction[index])
            criticalS8.append(critical[index])
            nThreadsS8.append(nThreads[index])

        if(n==9):

            serialS9.append(serial[index])
            reductionS9.append(reduction[index])
            criticalS9.append(critical[index])
            nThreadsS9.append(nThreads[index])
        index+=1



        

        
        

print(digits)


fig = plt.figure()
ax = plt.axes(projection='3d')
#ax.xscale("log")
#ax.yscale("log")

#ax.set_ylim3d(min, max)
#ax.set_zlim3d(min, max)
ax.set_xlabel('size(10^)')
ax.set_ylabel('nThreads')
ax.set_zlabel('time (log10)')


ax.scatter3D(digits, nThreads, serial, 'blue',s=20,alpha=0.5)
ax.scatter3D(digits, nThreads, reduction, 'green',s=20,alpha=0.5)
ax.scatter3D(digits, nThreads, critical, 'red',s=20,alpha=0.5)

plt.show()


plt.plot(digits2, critical2,c='orange')
plt.plot(digits2, serial2,c='blue')
plt.plot(digits10,reduction10,'red')
plt.plot(digits20,reduction20,'purple')

plt.scatter(digits20, serial20, s=50, c='blue',alpha=0.5)
plt.scatter(digits20, reduction20, s=50, c='green',alpha=0.5)
plt.scatter(digits20, critical20, s=50, c='red',alpha=0.5)

plt.scatter(digits10, serial10, s=50, c='blue',alpha=0.5)
plt.scatter(digits10, reduction10, s=50, c='green',alpha=0.5)
plt.scatter(digits10, critical10, s=50, c='red',alpha=0.5)

plt.scatter(digits2, serial2, s=50, c='blue',alpha=0.5)
plt.scatter(digits2, reduction2, s=50, c='green',alpha=0.5)
plt.scatter(digits2, critical2, s=50, c='red',alpha=0.5)

plt.xlabel('sizelog10')
plt.ylabel('time(log10')
plt.show()


plt.plot(nThreadsS8, serialS8,c='blue')
plt.plot(nThreadsS8,reductionS8,'red')
plt.plot(nThreadsS8,reductionS8,'purple')

plt.scatter(nThreadsS8, serialS8, s=50, c='blue',alpha=0.5)
plt.scatter(nThreadsS8, reductionS8, s=50, c='green',alpha=0.5)
plt.scatter(nThreadsS8, criticalS8, s=50, c='red',alpha=0.5)


plt.xlabel('nThreads')
plt.ylabel('time(log10')
plt.show()


colors=["red","green","blue","olive","orange","black","cyan","purple","pink","gold"]


s5=plt.plot(nThreadsS5, serialS5,c=colors[4])   
plt.plot(nThreadsS5,reductionS5,c=colors[4])
#plt.plot(nThreadsS6,reductionS6,'purple')

#plt.scatter(nThreadsS6, serialS6, s=50, c='blue',alpha=0.5)
plt.scatter(nThreadsS5, reductionS5, s=50, c=colors[4],alpha=0.5)
#plt.scatter(nThreadsS6, criticalS6, s=50, c='red',alpha=0.5)


s6=plt.plot(nThreadsS6, serialS6,c=colors[0])   
plt.plot(nThreadsS6,reductionS6,c=colors[0])
#plt.plot(nThreadsS6,reductionS6,'purple')

#plt.scatter(nThreadsS6, serialS6, s=50, c='blue',alpha=0.5)
plt.scatter(nThreadsS6, reductionS6, s=50, c=colors[0],alpha=0.5)
#plt.scatter(nThreadsS6, criticalS6, s=50, c='red',alpha=0.5)


s7=plt.plot(nThreadsS7, serialS7,c=colors[1])
plt.plot(nThreadsS7,reductionS7, c=colors[1])
#plt.plot(nThreadsS7,reductionS7,'purple')

#plt.scatter(nThreadsS7, serialS7, s=50, c='blue',alpha=0.5)
plt.scatter(nThreadsS7, reductionS7, s=50, c=colors[1],alpha=0.5)
#plt.scatter(nThreadsS7, criticalS7, s=50, c='red',alpha=0.5)


s8=plt.plot(nThreadsS8, serialS8,colors[2])
plt.plot(nThreadsS8,reductionS8,colors[2])
#plt.plot(nThreadsS8,reductionS8,'purple')

#plt.scatter(nThreadsS8, serialS8, s=50, c='blue',alpha=0.5)
plt.scatter(nThreadsS8, reductionS8, s=50, c=colors[2],alpha=0.5)
#plt.scatter(nThreadsS8, criticalS8, s=50, c='red',alpha=0.5)


s9=plt.plot(nThreadsS9, serialS9,c=colors[5])
plt.plot(nThreadsS9,reductionS9,colors[5])
#plt.plot(nThreadsS9,reductionS9,'purple')

#plt.scatter(nThreadsS9, serialS9, s=50, c='blue',alpha=0.5)
plt.scatter(nThreadsS9, reductionS9, s=50, c=colors[5],alpha=0.5)
#plt.scatter(nThreadsS9, criticalS9, s=50, c='red',alpha=0.5)

plt.xlabel('nThreads')
plt.ylabel('time(log10)')
#plt.legend(handles=([s9,s8,s7,s6],['size10^9','size10^8','size10^7','size10^6']),loc="upper left")
plt.show()




