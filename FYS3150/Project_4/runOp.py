from os import *
import time

# System setup
outfilename_average = "L20_avg_ordered.txt"
outfilename_mcc = "L20_mcc_ordered.txt"
L = 20
Tinitial = 1.0
Tfinal = 2.4
Tstep = 1.4
mcc = int(1e6)
write_mcc = 1
write_average = 1
printStatus = 1
steadyState = 1
useMPI = 0

# Compile C++ code first (all cpp-files)
system("mpicxx -std=c++11 -O3 -o mpitestrun.x main.cpp System.cpp")

# Command line argument
systemStr = "mpirun -n 1 ./mpitestrun.x %s %s %d %f %f %f %d %d %d %d %d %d" % (outfilename_average, outfilename_mcc, L, Tinitial, Tfinal, Tstep, mcc, write_mcc, write_average, printStatus, steadyState, useMPI)

# Start clock
start = time.time()

# Run program
system(systemStr)

# End clock
finish = time.time() 

# Runtime for program
runtime = finish - start

print "Runtime for program via Python script: %f s" %runtime