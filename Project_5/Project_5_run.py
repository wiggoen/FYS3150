from os import *
import time

# System setup
billOfAbundance = "noEqualityForFatCats.txt"
N = 50
m0 = 1e5
transactions = 1e7
runs = 10
alpha = 1
lambda_ = 0.25

# Compile C++ code first (all cpp-files)
system("g++ *.cpp -o main.x -O3 -std=c++11")

print "Starting to run the program."

# Command line argument
systemStr = "./main.x %s %d %f %d %d %f %f" % (billOfAbundance, N, m0, transactions, runs, alpha, lambda_)

start = time.time()         # Start clock

system(systemStr)           # Run program

finish = time.time()        # End clock

runtime = finish - start 

print "The python runtime of the program was %f s." %runtime

