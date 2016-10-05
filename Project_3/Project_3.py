from pylab import *

s = loadtxt("outputs/euler.txt")
x = s[:, 0]
y = s[:, 2]

plot(x, y)
show()