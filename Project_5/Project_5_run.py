from os import *
import time

# System setup
N = 500
m0 = 1.0
transactions = 1e7
runs = 1
alpha = 1
Lambda = [0, 0.25, 0.5, 0.9]
L = ["L0", "L025", "L05", "L09"]

# Compile C++ code first (all cpp-files)
system("g++ *.cpp -o main.x -O3 -std=c++11")

for i in range(len(Lambda)):
    print "Starting to run the program for L = %1.2f." %Lambda[i]
    billOfAbundance = "noEqualityForFatCats_c_"+L[i]+".txt"
    # Command line argument
    systemStr = "./main.x %s %d %f %d %d %f %f" % (billOfAbundance, N, m0, transactions, runs, alpha, Lambda[i])
    start = time.time()         # Start clock
    system(systemStr)           # Run program
    finish = time.time()        # End clock
    runtime = finish - start 
    print "The python runtime of the program for L = %g was %f s." %(Lambda[i], runtime)

