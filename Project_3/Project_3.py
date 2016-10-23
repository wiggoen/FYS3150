from itertools import *
from os import *
from pylab import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D
import time

"""
README: https://github.com/wiggoen/FYS3150/blob/master/Project_3/README.md
"""

# System setup
numTimesteps = 1000
dt = 0.001
outfilemode = "Python"
outfilename = "positions.xyz"
integrator = "Verlet"
systemstring = "Sun-Earth"
printEvery = 1
optimization_flag = "-O0"


# Compile C++ code first (all cpp-files)
system("g++ *.cpp -o main.x " + optimization_flag + " -std=c++11")

# Command line argument
systemStr = "./main.x %d %f %s %s %s %s %d" % (numTimesteps, dt, outfilemode, outfilename, integrator, systemstring, printEvery)

# Run program
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
        orbit = "Earth orbit"
    if systemstring == "Sun-Mercury":
        orbit = "Mercury orbit"
    if systemstring == "Sun-Mercury-GR":
        orbit = "Mercury orbit"
    if systemstring == "Planet-Escape":
        orbit = "Planet escape"
    lgd = legend(["Sun", orbit], loc="upper left", bbox_to_anchor=(1, 1))
    xlabel("x direction [AU]", fontsize = 16)
    ylabel("y direction [AU]", fontsize = 16)    
    art.append(lgd)
    tick_params(labelsize=14)
    axis("equal")
    savefig("plots/"+systemstring+"_"+integrator+".png", additional_artists=art, bbox_inches="tight")
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
        orbit1 = "Earth orbit"
        orbit2 = "Jupiter orbit"
    lgd = legend(["Sun", orbit1, orbit2], loc="upper left", bbox_to_anchor=(1, 1))
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
    ax.scatter(0, 0, 0, marker="o", color="#FFFF00") # Marks the spot of the Sun
    ax.set_xlabel("x direction [AU]", fontsize = 16, linespacing=2.5)
    ax.set_ylabel("y direction [AU]", fontsize = 16, linespacing=2.5)
    ax.set_zlabel("z direction [AU]", fontsize = 16, linespacing=2.5)
    art = []
    lgd = legend(["Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"], loc="upper left", bbox_to_anchor=(1, 1))
    art.append(lgd)
    tick_params(labelsize=14)
    savefig("plots/"+systemstring+".png", additional_artists=art, bbox_inches="tight")
    show()
    return "The system is calculated."

if outfilemode == "Python":
    positions = loadtxt("outputs/"+outfilename)
    if systemstring == "Sun-Earth" or systemstring == "Planet-Escape" or systemstring == "Sun-Mercury" or systemstring == "Sun-Mercury-GR":
        print Two_body(positions, systemstring)
    elif systemstring == "Sun-Earth-Jupiter":
        print Three_body(positions, systemstring)
    elif systemstring == "System-without-GR" or systemstring == "System-with-GR":
        print Ten_body(positions, systemstring)
    else:
        print "Choose a system."
else:
    print "Choose a system and outfilemode 'Python' if you want to plot with Python."
