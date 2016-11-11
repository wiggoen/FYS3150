from pylab import *

#source = loadtxt("outputs/outfile_b_states.txt")
source = loadtxt("outputs/outfile_c_states.txt")
#source2 = loadtxt("outputs/outfile_b_temp.txt")

MCC = 100000 # Monte Carlo Cycles
L = 20 # Lattice size


N = L*L # Number of spins

temp = source[:,0]
cycles = source[:,1]
E = source[:,2]
M = source[:,3]
Mabs = source[:,4]
meanE = source[:,5]
meanM = source[:,6]
accept = source[:,7]


plot(cycles[0:MCC-1], meanE[0:MCC-1]/N, cycles[MCC:], meanE[MCC:]/N)
#axis([0, cycles[-1], -10, 0])

xlabel("cycles")
ylabel("meanE")
legend(["E: T = 1.0", "E: T = 2.4"])
show()

#plot(cycles[0:MCC-1], meanM[0:MCC-1]/N, cycles[MCC:], meanM[MCC:]/N)
#hold("on")
plot(cycles[0:MCC-1], Mabs[0:MCC-1]/N, cycles[MCC:], Mabs[MCC:]/N)
xlabel("cycles")
ylabel("Mabs")
legend(["meanM: T = 1.0", "meanM: T = 2.4", "Mabs: T = 1.0", "Mabs: T = 2.4"])
show()

plot(temp[0:MCC-1], accept[0:MCC-1], temp[MCC:], accept[MCC:])
xlabel("Temp")
ylabel("Accept")
legend(["T = 1.0", "T = 2.4"])
show()

hist(meanE[0:MCC-1], bins=50)
show()

hist(meanE[MCC:], bins=50)
show()
