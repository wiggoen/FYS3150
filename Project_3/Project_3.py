from pylab import *

s = loadtxt("outputs/euler.txt")
x = s[:, 0]
y = s[:, 2]

plot(0, 0, "ro", x, y, x[0], y[0], "o")
title("The earth's orbit around the Sun")
legend(["Sun", "Earth orbit", "Earth startpoint"], loc=0)
show()