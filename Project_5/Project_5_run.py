from os import *
import time

# System setup
N = [500, 1000]
m0 = 1.0
transactions = 1e7
runs = 1e4
Alpha = [0.5, 1.0, 1.5, 2.0]
A = ["a0d5", "a1", "a1d5", "a2"]
Lambda = [0.25, 0.5, 0.9]
L = ["L0d25", "L0d5", "L0d9"]
Gamma = [0.0, 1.0, 2.0, 3.0, 4.0]
G = ["g0", "g1", "g2", "g3", "g4"]

# Compile C++ code first (all cpp-files)
system("g++ *.cpp -o main.x -O3 -std=c++11")

for k in range(len(N)):
    for j in range(len(Alpha)):
        for i in range(len(Lambda)):
            print "---"
            print "Starting to run the program for N = %g, L = %1.2f and A = %1.2f." %(N[k], Lambda[i], Alpha[j])
            billOfAbundance = "noEqualityForFatCats_N"+str(N[k])+"_"+L[i]+"_"+A[j]+".txt"
            # Command line argument
            systemStr = "./main.x %s %d %f %d %d %f %f" % (billOfAbundance, N[k], m0, transactions, runs, Alpha[j], Lambda[i])
            start = time.time()         # Start clock
            system(systemStr)           # Run program
            finish = time.time()        # End clock
            runtime = finish - start 
            print "The python runtime of the program for L = %g was %f s." %(Lambda[i], runtime)

