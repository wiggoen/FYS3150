from pylab import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D

positions = loadtxt("outputs/positions.xyz")
num = 2#10 # Number of Celestial bodies

fig = figure()
ax = fig.add_subplot(111, projection="3d")
for i in range(num):
    plot(positions[i::num][:, 0], positions[i::num][:, 1], positions[i::num][:, 2])
    hold("on")
ax.scatter(0, 0, 0, marker="o", color="r")
#ax.scatter(x[0], y[0], z[0], marker="o", color="g")
title("The Solar System", fontsize = 18)
ax.set_xlabel("x direction [AU]", fontsize = 16, linespacing=2.5)
ax.set_ylabel("y direction [AU]", fontsize = 16, linespacing=2.5)
ax.set_zlabel("\n" + "z direction [AU]", fontsize = 16, linespacing=2.5)
art = []
lgd = legend(["Sun", "Earth orbit"],loc="upper left", bbox_to_anchor=(1, 1))
art.append(lgd)
tick_params(labelsize=14, pad=100)
savefig("plots/SolarSystem3D.png", additional_artists=art, bbox_inches="tight")
show()

