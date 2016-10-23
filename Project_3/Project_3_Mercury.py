from itertools import *
from os import *
from pylab import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D
import time

"""
README: https://github.com/wiggoen/FYS3150/blob/master/Project_3/README.md

Mercury: 
numTimesteps = 1e9
dt = 1e-7
"""

theta = loadtxt("outputs/perihelion.txt")
theta_Newtonian = loadtxt("outputs/Perihelion_wo_GR.txt")

print "The ratio between perihelion precession with Newtonian force and with GR = %E" %(abs(theta_Newtonian[-1]/theta[-1]))

t = arange(0, len(theta))

figure(1)
plot(t, theta, "-b", [0, t[-1]], [0.0002085, 0.0002085], "-r")
art = []
lgd = legend(["Perihelion angle", "Predicted 43'' per century"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Time [years on Mercury]", fontsize = 16)
ylabel(r"$\theta_p$ [rad]", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
savefig("plots/Mercury_perihelion.png", additional_artists=art, bbox_inches="tight")
figure(1).set_tight_layout(True)
show()
