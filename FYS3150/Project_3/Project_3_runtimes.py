from os import *
from pylab import *
import time

"""
This program is probably written in a stupid brute force way. 
It takes over 11 minutes to compute.
README: https://github.com/wiggoen/FYS3150/blob/master/Project_3/README.md
"""

# System setup
numTimesteps = [100000, 150000, 200000, 250000, 300000, 400000]
dt = 0.001
outfilemode = "Ovito"               # Use "Ovito" or "Python" for writing to the file
outfile = "positions.xyz"           # Name of output file
integrator = ["Euler", "Verlet"]    # Use "Verlet" or "Euler" for integrator
systemstring = "System-runtime"     # Use "Sun-Earth", "Planet-Escape", "Sun-Mercury", "Sun-Mercury-GR", "Sun-Earth-Jupiter", "System-without-GR" or "System-with-GR"
printEvery = 1                      # Prints every specified timestep to file (1 means all timesteps), use 0 for runtime test
optimization_flag = ["-O0", "-O3"]  # Default is -O0, use -O3 for optimization
numberOfLoops = 10                  # Default is 0, use i.e. 10 with "System-runtime"


def runProgram(numberOfLoops, numTimesteps, optimization_flag, integrator):
    # Compile C++ code first (all cpp-files)
    system("g++ *.cpp -o main.x " + optimization_flag + " -std=c++11")
    # Command line argument
    systemStr = "./main.x %d %f %s %s %s %s %d" % (numTimesteps, dt, outfilemode, outfile, integrator, systemstring, printEvery)
    runtimes = zeros(numberOfLoops)
    for i in xrange(numberOfLoops):
        # Start clock
        start = time.time()
        # Run program
        system(systemStr)
        # End clock
        finish = time.time()  
        # Time used
        runtimes[i] = finish - start      
    return "Program looped %d times for %d time steps using the %s method with optimization flag '%s'. \n Average runtime was: %f s." %(numberOfLoops, numTimesteps, integrator, optimization_flag, sum(runtimes)/float(numberOfLoops))

for j in xrange(len(numTimesteps)):
    for k in xrange(len(integrator)):
        for l in xrange(len(optimization_flag)):
            print runProgram(numberOfLoops, numTimesteps[j], optimization_flag[l], integrator[k])

