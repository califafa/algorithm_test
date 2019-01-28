#生成complex ,生成快速傅里叶变换所需要的旋转子

import math

sin=math.sin
cos=math.cos
pi=math.pi

class C:
    real=0
    img=0

len=16

wn=[]

for i in range(len):
    a=C()
    a.real=cos((pi/len)*i)
    a.img=-1*sin((pi/len)*i)
    wn.append(a)

for i in range(len):
    print('{',wn[i].real,',',wn[i].img,'}',',')