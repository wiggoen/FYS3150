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
		# Using slicing to get the right "area" of the file
		A[j] = float(line[16:19].strip())
		Z[j] = float(line[11:14].strip())
		j += 1

N = A-Z 	 	# Neutron number

MagicNumbers = array([2, 8, 20, 28, 50, 82, 126])
MagicPairs = array([[2, 2],
					[8, 8],
					[20, 8],
					[20, 20],
					[20, 28],
					[28, 20],
					[28, 28],
					[50, 28],
					[50, 50],
					[82, 50],
					[126, 82]])

Nmagic = MagicPairs[:, 0]
Zmagic = MagicPairs[:, 1]

# Plot of Chart of nuclides, Z vs N
fig1 = figure(1)
plot(N, Z, "x", [0, 120], [0, 120], "k-") 	# Nuclides and Z = N line
plot(Nmagic, Zmagic, "ro") 					# Magic numbers
plot([1, 24], [8, 8], "m-", [20, 20], [4, 32], "m-", [10, 42], [20, 20], "m-", 
	 [28, 28], [10, 36], "m-", [16, 55], [28, 28], "m-", [50, 50], [24, 54], "m-",
	 [45, 92], [50, 50], "m-", [82, 82], [42, 76], "m-", [90, 145], [82, 82], "m-",
	 [126, 126], [72, 97], "m-") 			# Lines for magic numbers
title("Chart of Nuclides, Z vs N", fontsize=20)
xlabel("Neutron number, N", fontsize=16)
ylabel("Porton number, Z", fontsize=16)
legend(["Nuclides", "Z = N", "Magic numbers"], loc=0)
tick_params(labelsize=14)
fig1.set_tight_layout(True) # Minimizing overlap of labels
savefig("CoN.png") # Saving figure to .png
#show()


# Plot of Chart of nuclides, Z vs A
fig2 = figure(2)
plot(A, Z, "x", [0, 240], [0, 120], "k-") 	# Nuclides and Z = A/2 line
title("Chart of Nuclides, Z vs A", fontsize=20)
xlabel("Mass number, A", fontsize=16)
ylabel("Proton number, Z", fontsize=16)
legend(["Nuclides", "Z = A/2"], loc=0)
tick_params(labelsize=14)
fig2.set_tight_layout(True) # Minimizing overlap of labels
savefig("CoN2.png") # Saving figure to .png
#show()


# Plot of Chart of nuclides, Z/A vs A 
fig3 = figure(3)
plot(A, Z/A, "x", [0, 294], [0.5, 0.5], "k-")
title("Chart of Nuclides, Z/A vs A", fontsize=20)
xlabel("Mass number, A", fontsize=16)
ylabel("Z/A", fontsize=16)
legend(["Nuclides", "Z/A = 1/2"], loc=0)
tick_params(labelsize=14)
fig3.set_tight_layout(True) # Minimizing overlap of labels
savefig("CoN3.png") # Saving figure to .png
show()

