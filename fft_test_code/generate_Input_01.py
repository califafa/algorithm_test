#生成complex ,生成快速傅里叶变换所需要的输入

import math

sin=math.sin
cos=math.cos
pi=math.pi

class C:
    real=0
    img=0

len=32

period=4

freq=period*2*pi/len



inpuT=[]

for i in range(len):
    a=C()
    a.real=cos(freq*i)
 #  a.real=cos((pi/len)*i)
 #   a.img=-1*sin((pi/len)*i)
    inpuT.append(a)

for i in range(len):
    print('{',inpuT[i].real,',',inpuT[i].img,'}',',')
