from itertools import *
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
systemstring = "Sun-Earth"      # Use "Sun-Earth", "Planet-Escape", "Sun-Mercury", "Sun-Mercury-GR", "Sun-Earth-Jupiter", "System-without-GR" or "System-with-GR"
printEvery = 1                  # Prints every specified timestep to file (1 means all timesteps)
optimization_flag = "-O0"       # Default is -O0, use -O3 for optimization

# Compile C++ code first (all cpp-files)
system("g++ *.cpp -o main.x " + optimization_flag + " -std=c++11")

# Run program
systemStr = "./main.x %d %f %s %s %s %s %d" % (numTimesteps, dt, outfilemode, outfile, integrator, systemstring, printEvery)
system(systemStr)

# Two body systems
def Two_body(positions, systemstring):
    num = 2 # Number of Celestial bodies
    fig = figure()
    if systemstring == "Sun-Earth" or systemstring == "Planet-Escape":
        #                  Sun,      Earth
        colors = cycle(["#FF0000", "#00008B"])
    if systemstring == "Sun-Mercury" or systemstring == "Sun-Mercury-GR":
        #                  Sun,      Mercury
        colors = cycle(["#FF0000", "#939393"])
    for i in range(num):
        plot(positions[i::num][:, 0], positions[i::num][:, 1], color=next(colors))
        hold("on")
    plot(0, 0, marker="o", color="#FF0000") # Marks the spot of the Sun
    art = []
    if systemstring == "Sun-Earth":
        title("The "+systemstring+" system, \n timesteps = %d" %numTimesteps, fontsize = 18)
        orbit = "Earth orbit"
    if systemstring == "Sun-Mercury":
        title("The "+systemstring+" system, \n timesteps = %d" %numTimesteps, fontsize = 18)
        orbit = "Mercury orbit"
    if systemstring == "Sun-Mercury-GR":
        title("The Sun-Mercury system with GR, \n timesteps = %d" %numTimesteps, fontsize = 18)
        orbit = "Mercury orbit"
    if systemstring == "Planet-Escape":
        title("The planet escape system, \n timesteps = %d" %numTimesteps, fontsize = 18)
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

# Three body systems
def Three_body(positions, systemstring):
    num = 3 # Number of Celestial bodies
    fig = figure()
    if systemstring == "Sun-Earth-Jupiter":
        #                  Sun,      Earth,     Jupiter
        colors = cycle(["#FF0000", "#00008B", "#FF9933"])
    for i in range(num):
        plot(positions[i::num][:, 0], positions[i::num][:, 1], color=next(colors))
        hold("on")
    plot(0, 0, marker="o", color="#FF0000") # Marks the spot of the Sun
    art = []
    if systemstring == "Sun-Earth-Jupiter":
        title("The "+systemstring+" system, \n timesteps = %d" %numTimesteps, fontsize = 18)
        orbit1 = "Earth orbit"
        orbit2 = "Jupiter orbit"
    lgd = legend(["Sun", orbit1, orbit2],loc="upper left", bbox_to_anchor=(1, 1))
    xlabel("x direction [AU]", fontsize = 16)
    ylabel("y direction [AU]", fontsize = 16)    
    art.append(lgd)
    tick_params(labelsize=14)
    axis("equal")
    savefig("plots/"+systemstring+".png", additional_artists=art, bbox_inches="tight")
    show()
    return "The system is calculated."

# Ten body systems
def Ten_body(positions, systemstring):
    num = 10 # Number of Celestial bodies
    fig = figure()
    ax = fig.add_subplot(111, projection="3d")
    #                  Sun,     Mercury,    Venus,     Earth,     Mars,     Jupiter,    Saturn,    Uranus,   Neptune,    Pluto
    colors = cycle(["#FFFF00", "#939393", "#FF6600", "#00008B", "#FF0000", "#FF9933", "#FF6600", "#00FFFF", "#0000FF", "#808080"])
    for i in range(num):
        plot(positions[i::num][:, 0], positions[i::num][:, 1], positions[i::num][:, 2], color=next(colors))
        hold("on")
    ax.scatter(0, 0, 0, marker="o", color="#FFFF00")
    if systemstring == "System-without-GR":
        title("The solar system without GR, \n timesteps = %d" %numTimesteps, fontsize = 18)
    if systemstring == "System-with-GR":
        title("The solar system with GR on Mercury, \n timesteps = %d" %numTimesteps, fontsize = 18)
    ax.set_xlabel("x direction [AU]", fontsize = 16, linespacing=2.5)
    ax.set_ylabel("y direction [AU]", fontsize = 16, linespacing=2.5)
    ax.set_zlabel("z direction [AU]", fontsize = 16, linespacing=2.5)
    art = []
    lgd = legend(["Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"],loc="upper left", bbox_to_anchor=(1, 1))
    art.append(lgd)
    tick_params(labelsize=14, pad=100)
    savefig("plots/"+systemstring+".png", additional_artists=art, bbox_inches="tight")
    show()
    return "The system is calculated."

if outfilemode == "Python":
    positions = loadtxt("outputs/"+outfile)
    if systemstring == "Sun-Earth" or systemstring == "Planet-Escape" or systemstring == "Sun-Mercury" or systemstring == "Sun-Mercury-GR":
        print Two_body(positions, systemstring)
    if systemstring == "Sun-Earth-Jupiter":
        print Three_body(positions, systemstring)
    if systemstring == "System-without-GR" or systemstring == "System-with-GR":
        print Ten_body(positions, systemstring)
    else:
        print "Choose a system."
