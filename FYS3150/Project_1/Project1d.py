from matplotlib.pyplot import *
from numpy import *

x = 10

def F(x):
    x = str(x)
    string = 'out-' + x + '.txt'
    file = loadtxt(string)
    v = file[:]
    x = linspace(0, 1, len(v))
    u = 1-(1-exp(-10))*x-exp(-10*x)
    return x, v, u

x, v, u = F(x)
h, epsilon, 

figure(1)
plot(x, u, '-b', x, v, 'or')
title("?")
xlabel("?")
ylabel("?")
legend(["u", "v"])
show()