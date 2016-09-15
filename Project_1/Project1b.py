from matplotlib.pyplot import *
from numpy import *

N10 = loadtxt('out-10.txt')
#N100 = loadtxt('out-100.txt')
#N1000 = loadtxt('out-1000.txt')

v10 = N10[:]
#v100 = N100[:, 4]
#v1000 = N1000[:, 4]

# setting boundary condition for v_p[0] and v_p[N+1]
v_p10 = zeros(10+2) 
#v_p100 = zeros(100+2) 
#v_p1000 = zeros(1000+2) 

# filling the inner points of the vector (not changing boundaries)
for i in range(1,11): 
    v_p10[i] = v10[i-1]

#for i in range(1, 101):
#    v_p100[i] = v100[i-1]

#for i in range(1, 1001):
#    v_p1000[i] = v1000[i-1]

x1 = linspace(0, 1, 12)
#x2 = linspace(0, 1, 102)
#x3 = linspace(0, 1, 1002)

u1 = 1-(1-exp(-10))*x1-exp(-10*x1)
#u2 = 1-(1-exp(-10))*x2-exp(-10*x2)
#u3 = 1-(1-exp(-10))*x3-exp(-10*x3)

figure(1)
plot(x1, u1, '-b', x1, v_p10, 'or')
#figure(2)
#plot(x2, u2, '-b', x2, v_p100, 'or')
#figure(3)
#plot(x3, u3, '-b', x3, v_p1000, 'or')
legend(["u", "v"])
show()