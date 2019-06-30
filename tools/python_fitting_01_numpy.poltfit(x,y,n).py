#enviroment: anaconda python3.5
#implement: numpy.polyfit(x,y,n), result: y = a*x^n+b*x^(n-1)+......

import numpy as np 
import matplotlib.pyplot as plt 
import random

datLen=10
fitLen=12

x=[]
for i in range(datLen):
    x.append(i)

x1=[]
for i in x:
    for j in range(100):
        x1.append(i+0.01*j)

#x=np.array(x)
print('x is:\n',x)
print('x1 is:\n',x1)

num=[]
for i in x:
    num.append(random.randint(0,100))

y=num#np.array(num)

print('y is:\n',y)

f1=np.polyfit(x,y,fitLen)#f1=[a,b,c,d,....],即 a*x^n+b*x^(n-1)+.....+常数
print('f1 is :\n',f1)

p1=np.poly1d(f1)
#print('p1 is :\n',p1)
#p1就是拟合的函数, f1是其各项系数
yvals=p1(x1)
#print("yvals is :\n",yvals)

plot1 = plt.plot(x, y, 's',label='original values')
plot2 = plt.plot(x1, yvals, 'r',label='polyfit values')
plt.xlabel('x')
plt.ylabel('y')
plt.legend(loc=4) #指定legend的位置右下角
plt.title('polyfitting')
plt.show()

print("\n\n\n\nResult:\n\n\n")

print('y = ')
for i in range(len(f1)):
    print(f1[i],'*','(','x','^',fitLen-i,')')
    if(i<fitLen):
        print('+')