from pylab import *

source_mcc = loadtxt("outputs/outfile_c_mcc.txt")
#source_average = loadtxt("outputs/outfile_c_average.txt")

MCC = 1000000               # Monte Carlo Cycles
L = 20                      # Lattice size
N = L*L                     # Number of spins

T = source_mcc[:,0]         # Temperature
cycles = source_mcc[:,1]    # Monte Carlo Cycles
E = source_mcc[:,2]         # Energy
M = source_mcc[:,3]         # Magnetization
absM = source_mcc[:,4]      # Absolute value of magnetization
meanE = source_mcc[:,5]     # Current mean energy per cycle
meanM = source_mcc[:,6]     # Current mean magnetization per cycle
aC = source_mcc[:,7]        # Accepted configurations

skip = 100
plot(cycles[0:MCC-1:skip], meanE[0:MCC-1:skip])
#axis([0, cycles[-1], -10, 0])
xlabel("Cycles")
ylabel("Current mean energy per cycle")
legend(["E: T = 1.0"])
show()

plot(cycles[MCC::skip], meanE[MCC::skip])
xlabel("Cycles")
ylabel("Current mean energy per cycle")
legend(["E: T = 2.4"])
show()


#plot(cycles[0:MCC-1], meanM[0:MCC-1]/N, cycles[MCC:], meanM[MCC:]/N)
#hold("on")
"""
plot(cycles[0:MCC-1], abs(absM[0:MCC-1]/N))#, cycles[MCC:], abs(absM[MCC:]/N))
xlabel("cycles")
ylabel("absM")
legend(["meanM: T = 1.0", "meanM: T = 2.4", "Mabs: T = 1.0", "Mabs: T = 2.4"])
show()
"""

"""
plot(cycles[0:MCC-1], aC[0:MCC-1])#, T[MCC:], aC[MCC:])
xlabel("Number of Monte Carlo cycles")
ylabel("Accepted states")
legend(["T = 1.0"])#, "T = 2.4"])
show()

plot(cycles[MCC:], aC[MCC:])#, T[MCC:], aC[MCC:])
xlabel("Number of Monte Carlo cycles")
ylabel("Accepted states")
legend(["T = 2.4"])#, "T = 2.4"])
show()
"""

"""
hist(meanE[0:MCC-1], bins=25)
show()

hist(meanE[MCC:], bins=25)
show()
"""
