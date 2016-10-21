from itertools import *
from os import *
from pylab import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D

"""
README: https://github.com/wiggoen/FYS3150/blob/master/Project_3/README.md
"""

# Loading data
SE = loadtxt("outputs/sun-earth.txt")           # Sun-Earth
SEJ = loadtxt("outputs/sun-earth-jupiter.txt")  # Sun-Earth-Jupiter

# Sun-Earth with and without Jupiter
def Sun_Earth(SE, SEJ):
    fig = figure()
    plot(0, 0, "or", SE[1::2][:, 0], SE[1::2][:, 1], "-b", SEJ[1::3][:, 0], SEJ[1::3][:, 1], '-g')
    art = []
    title("Earth's orbit with and without Jupiter, \n timesteps = 12000", fontsize = 18)
    lgd = legend(["Sun", "Earth orbit without Jupiter", "Earth orbit with Jupiter"], loc="upper left", bbox_to_anchor=(1, 1))
    xlabel("x direction [AU]", fontsize = 16)
    ylabel("y direction [AU]", fontsize = 16)    
    art.append(lgd)
    tick_params(labelsize=14)
    axis("equal")
    savefig("plots/Sun-Earth_w_wo-Jupiter.png", additional_artists=art, bbox_inches="tight")
    show()
    return "The system has been plotted."

Sun_Earth(SE, SEJ)
