from os import *
import time

# System setup
N = [500, 1000]
m0 = 1.0
transactions = 10
runs = 10
Alpha = [0.5, 1.0, 1.5, 2.0]
A = ["a05", "a1", "a15", "a2"]
Lambda = [0.25, 0.5, 0.9]
L = ["L025", "L05", "L09"]
Gamma = [0.0, 1.0, 2.0, 3.0, 4.0]
G = ["g0", "g1", "g2", "g3", "g4"]

# Compile C++ code first (all cpp-files)
system("g++ *.cpp -o main.x -O3 -std=c++11")

for m in range(len(Gamma)):
    for k in range(len(N)):
        for j in range(len(Alpha)):
            for i in range(len(Lambda)):
                print "---"
                print "Starting to run the program for N = %g, L = %g, A = %g and G = %g." %(N[k], Lambda[i], Alpha[j], Gamma[m])
                billOfAbundance = "noEqualityForFatCats_N"+str(N[k])+"_"+L[i]+"_"+A[j]+"_"+G[m]+".txt"
                # Command line argument
                systemStr = "./main.x %s %d %f %d %d %f %f %f" % (billOfAbundance, N[k], m0, transactions, runs, Alpha[j], Lambda[i], Gamma[m])
                start = time.time()         # Start clock
                system(systemStr)           # Run program
                finish = time.time()        # End clock
                runtime = finish - start 
                print "The python runtime of the program for N = %g, L = %g, A = %g and G = %g was %f s." %(N[k], Lambda[i], Alpha[j], Gamma[m], runtime)

