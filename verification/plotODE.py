import matplotlib.pyplot as plt
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np


plt.figure(1)
err_euler = [5.399415029016189e-01,3.2397983285888388e-01,1.1395821464720407e-01,3.6466240008739409e-02,1.1545466055784317e-02]
err_euler_last = [5.9399415029016189e-01,1.6203959754804498e-01, 1.9543765637294583e-02, 1.9953439760985819e-03, 1.9995334380586797e-04]
err_rk4 = [2.2435933552675788e-08,1.4180517734563533e-08,1.4444299072996727e-11,9.9647356857658821e-14,6.7108708484489054e-13]
err_rk45 = [4.0426699485508921e-09,1.6604457840609665e-09,3.1504912222427475e-13,9.8685741833700703e-14,7.1147491585113869e-13]
err_rk8 = [3.0580752103652577e-10,6.1302957777329402e-15,1.6467657285282579e-14,9.7243319297763550e-14,6.8923756842210327e-13]
h = [1,0.1,0.01,0.001,0.0001]

log_euler = [np.log(err_euler[i]) for i in range(len(err_euler))]
log_euler_last = [np.log(err_euler_last[i]) for i in range(len(err_euler_last))]
log_rk4 = [np.log(err_rk4[i]) for i in range(len(err_rk4))]
log_rk45 = [np.log(err_rk45[i]) for i in range(len(err_rk45))]
log_rk8 = [np.log(err_rk8[i]) for i in range(len(err_rk8))]
log_h = [np.log(h[i]) for i in range(len(h))]

plt.plot(log_h, log_euler_last)
plt.title("The log-log convergence analysis for Forward Euler Method")
plt.xlabel("log(h)")
plt.ylabel("log(err)")
plt.grid(True)
#plt.show()
plt.savefig("convergence_euler.png")

plt.figure(2)
plt.plot(log_h, log_rk4)
plt.plot(log_h, log_rk45)
plt.plot(log_h, log_rk8)
plt.legend(['rk4', 'rk45', 'rk8'], loc='upper left')
plt.xlabel("log(h)")
plt.ylabel("log(err)")
plt.grid(True)
#plt.show()
plt.savefig("convergence_rk.png")

x = np.zeros(101)
y = np.zeros(101)
z = np.zeros(101)
i=0

with open('output.dat') as infile:
    for line in infile:
#        time = line.split()[0]
        x[i] = line.split()[1]
        y[i] = line.split()[2]
        z[i] = line.split()[3]
        i = i+1

print x,len(x)
print y,len(y)
print z,len(z)
fig = plt.figure(3)
ax = fig.gca(projection='3d')
ax.plot(x, y, z, label='ODEsolver trajectory curve')
ax.legend()
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')
ax.grid(True)
#plt.show()
plt.savefig("ODE_trajectory.png")
