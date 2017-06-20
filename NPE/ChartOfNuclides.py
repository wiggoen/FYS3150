# Proposed solution is written in Python 3.6.1.
# Chart of nuclides

from matplotlib.pyplot import *
from numpy import *

data = "mass16.txt" # Datafile: https://www-nds.iaea.org/amdc/ame2016/mass16.txt

n = 3475-39		# Number of nuclides in datafile
A = zeros(n) 	# Mass number
Z = zeros(n) 	# Proton number

with open(data, "r") as datafile:
	# Skip the first 39 lines in datafile
	for i in xrange(39):
		datafile.readline()
	# Do analysis for the rest of the lines in datafile
	j = 0
	for line in datafile:
		A[j] = float(line[16:19].strip())
		Z[j] = float(line[11:14].strip())
		j += 1
 
N = A-Z 	 	# Neutron number

# Plot of Chart of nuclides
fig1 = figure(1)
plot(A, N, "x", [0, 120], [0, 120], "k-")
title("Chart of Nuclides", fontsize=20)
xlabel("Neutron number, N", fontsize=16)
ylabel("Porton number, Z", fontsize=16)
legend(["Nuclides", "Z = N"], loc=0)
tick_params(labelsize=14)
fig1.set_tight_layout(True) # Minimizing overlap of labels
savefig("CoN.png") # Saving png
show()

