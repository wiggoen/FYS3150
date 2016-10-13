from pylab import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D

positions = loadtxt("outputs/positions.xyz")# pos.xyz")
#           Sun,       
scolor = ["#FFBF00"]
#           Earth,    Jupiter,   Venus,      Mars,     Saturn,    Uranus,    Neptune,    Pluto,    Mercury
colors = ["#0048BA", "#CC7722", "#81613C", "#C46210", "#CC9966", "#87CEEB", "#6495ED", "#996515", "#987654"]
num = 2 # Number of Celestial bodies

fig = figure()
ax = fig.add_subplot(111, projection="3d")
for i in range(num):
    plot(positions[i::num][:, 0], positions[i::num][:, 1], positions[i::num][:, 2])
    hold("on")
ax.scatter(0, 0, 0, marker="o", color="r")# =scolor[0])
#ax.scatter(x[0], y[0], z[0], marker="o", color="g")
title("The Solar System", fontsize = 18)
ax.set_xlabel("x direction [AU]", fontsize = 16, linespacing=2.5)
ax.set_ylabel("y direction [AU]", fontsize = 16, linespacing=2.5)
ax.set_zlabel("z direction [AU]", fontsize = 16, linespacing=2.5)
art = []
#lgd = legend(["Sun", "Earth orbit"],loc="upper left", bbox_to_anchor=(1, 1))
#art.append(lgd)
tick_params(labelsize=14, pad=100)
savefig("plots/SolarSystem3D_SE.png", additional_artists=art, bbox_inches="tight")
show()

