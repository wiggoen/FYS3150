from os import *
from pylab import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D

# Setup
numTimesteps = 1000
dt = 0.001
outfilemode = "Python"          # Use "Ovito" or "Python" for writing to the file
outfile = "positions.xyz"       # Name of output file
integrator = "Verlet"           # Use "Verlet" or "Euler" for integrator
systemstring = "System-with-GR"    # Use "Sun-Earth", "Planet-Escape", "Sun-Mercury", "System-without-GR" or "System-with-GR"
printEvery = 1                  # Prints every specified timestep to file (1 means all timesteps)
optimization_flag = "-O0"       # Default is -O0, use -O3 for optimization

# Compile C++ code first (all cpp-files)
system("g++ *.cpp -o main.x " + optimization_flag + " -std=c++11")

# Run program
systemStr = "./main.x %d %f %s %s %s %s %d" % (numTimesteps, dt, outfilemode, outfile, integrator, systemstring, printEvery)
system(systemStr)

# Colors
#           Sun,       
#scolor = ["#FFBF00"]
#           Earth,    Jupiter,   Venus,      Mars,     Saturn,    Uranus,    Neptune,    Pluto,    Mercury
#colors = ["#0048BA", "#CC7722", "#81613C", "#C46210", "#CC9966", "#87CEEB", "#6495ED", "#996515", "#987654"]

# Two body systems
def Two_body(positions, systemstring):
    num = 2 # Number of Celestial bodies
    fig = figure()
    for i in range(num):
        plot(positions[i::num][:, 0], positions[i::num][:, 1])
        hold("on")
    plot(0, 0, marker="o", color="b") # marks the spot of the Sun
    art = []
    if systemstring == "Sun-Earth":
        title("The "+systemstring+" system", fontsize = 18)
        orbit = "Earth orbit"
    if systemstring == "Sun-Mercury":
        title("The "+systemstring+" system", fontsize = 18)
        orbit = "Mercury orbit"
    if systemstring == "Planet-Escape":
        title("The planet escape system", fontsize = 18)
        orbit = "Planet escape"
    lgd = legend(["Sun", orbit],loc="upper left", bbox_to_anchor=(1, 1))
    xlabel("x direction [AU]", fontsize = 16)
    ylabel("y direction [AU]", fontsize = 16)    
    art.append(lgd)
    tick_params(labelsize=14)
    axis("equal")
    savefig("plots/"+systemstring+".png", additional_artists=art, bbox_inches="tight")
    show()
    return "The system is calculated."

#"System-without-GR" or "System-with-GR"
 #if systemstring == "System-without-GR" or systemstring == "System-with-GR": 
 #       num = 10 # Number of Celestial bodies

# Two body systems
def Ten_body(positions, systemstring):
    num = 10 # Number of Celestial bodies
    fig = figure()
    ax = fig.add_subplot(111, projection="3d")
    for i in range(num):
        plot(positions[i::num][:, 0], positions[i::num][:, 1], positions[i::num][:, 2])
        hold("on")
    ax.scatter(0, 0, 0, marker="o", color="r")# =scolor[0])
    #ax.scatter(x[0], y[0], z[0], marker="o", color="g")
    if systemstring == "System-without-GR":
        title("The solar system without GR", fontsize = 18)
    if systemstring == "System-with-GR":
        title("The solar system with GR on Mercury", fontsize = 18)
    ax.set_xlabel("x direction [AU]", fontsize = 16, linespacing=2.5)
    ax.set_ylabel("y direction [AU]", fontsize = 16, linespacing=2.5)
    ax.set_zlabel("z direction [AU]", fontsize = 16, linespacing=2.5)
    art = []
    #lgd = legend(["Sun", "Earth orbit"],loc="upper left", bbox_to_anchor=(1, 1))
    #art.append(lgd)
    tick_params(labelsize=14, pad=100)
    savefig("plots/"+systemstring+".png", additional_artists=art, bbox_inches="tight")
    show()
    return "The system is calculated."

if outfilemode == "Python":
    positions = loadtxt("outputs/"+outfile)
    if systemstring == "Sun-Earth" or systemstring == "Planet-Escape" or systemstring == "Sun-Mercury":
        print Two_body(positions, systemstring)
    if systemstring == "System-without-GR" or systemstring == "System-with-GR":
        print Ten_body(positions, systemstring)
    else:
        print "Choose a system."



