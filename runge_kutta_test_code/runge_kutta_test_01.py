import numpy as np
import matplotlib.pyplot as plt

# print(plt.style.available)
plt.style.use("seaborn-colorblind")


class Runge_Kutta:
    def __init__(self, x_init, y_init, step, times):
        self.x_init = x_init
        self.y_init = y_init
        self.step = step
        self.times = times
        self.x_coordinate = [x_init]
        self.y_predict = [y_init]
        self.y_real = [y_init]
        self.relative_error = [0]
        self.sum=[0]

    def derivatives_fun(self, x, y):
        return 3*(x**2)+30

    def real_fun(self, x):
        return x**3+30*x

    def rf4(self):
        directe_add=0
        for i in range(self.times):
            k1 = self.derivatives_fun(self.x_init, self.y_init)
            k2 = self.derivatives_fun(self.x_init + self.step / 2, self.y_init + self.step * k1 / 2)
            k3 = self.derivatives_fun(self.x_init + self.step / 2, self.y_init + self.step * k2 / 2)
            k4 = self.derivatives_fun(self.x_init + self.step, self.y_init + self.step * k3)
            y_end = self.y_init + self.step * (k1 + 2 * k2 + 2 * k3 + k4) / 6
            # print(y_end)
            x_end = self.x_init + self.step
            relative_error = abs(y_end - self.real_fun(x_end))
            directe_add+=self.derivatives_fun(self.x_init,self.y_init)
            self.sum.append(directe_add)
            self.x_init = x_end
            self.y_init = y_end
            self.y_real.append(self.real_fun(x_end))
            self.x_coordinate.append(x_end)
            self.y_predict.append(y_end)
            self.relative_error.append(relative_error)



#runge_kutta 和 直接相加的对比

def main():
    # 传入初始位置坐标（x_init, y_init）步长step，迭代次数times
    rk4 = Runge_Kutta(0, 0, 0.05, 10000)
    rk4.rf4()
    # print(rk4.y_predict)

    plt.figure(1)
    plt.subplot(211)

    plt.plot(np.array(rk4.x_coordinate), np.array(rk4.y_real), 'b')
    plt.plot(np.array(rk4.x_coordinate), np.array(rk4.y_predict), 'ro')
    #plt.plot(np.array(rk4.x_coordinate), np.array(rk4.sum),'go')

    plt.subplot(212)

    rk_err_percent=[]
    for i in range(len(rk4.y_real)):
        if(rk4.y_real[i]):
            rk_err_percent.append(rk4.relative_error[i]/rk4.y_real[i])
        else:
            rk_err_percent.append(0)
    plt.plot(np.array(rk4.x_coordinate), np.array(rk_err_percent))

    #plt.plot(np.array(rk4.x_coordinate), np.array(rk4.relative_error))
    plt.show()
    #plt.figure(1)
    plt.subplot(211)
    plt.plot(np.array(rk4.x_coordinate), np.array(rk4.y_real), 'b')

    scale=rk4.y_real[100]/rk4.sum[100]  #选择第100次的值作为缩放的标准
    for i in range(len(rk4.sum)):
        rk4.sum[i]*=scale

    plt.plot(np.array(rk4.x_coordinate), np.array(rk4.sum),'ro')
    
    plt.subplot(212)

    add_err=[]
    add_err_percent=[]
    for i in range(len(rk4.sum)):
        add_err.append(abs(rk4.y_real[i]-rk4.sum[i]))
        if(rk4.y_real[i]):
            add_err_percent.append(add_err[i]/rk4.y_real[i])
        else:
            add_err_percent.append(0)

    plt.plot(np.array(rk4.x_coordinate), np.array(add_err_percent),'b')

    plt.show()

    print(rk4.sum[-1])
    print(rk4.y_real[-1])

if __name__ == '__main__':
    main()
