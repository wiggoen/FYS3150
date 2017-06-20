# Proposed solution is written in Python 3.6.1.
# Binding energy per nucleon

from matplotlib.pyplot import *
from numpy import *

# Range of A
A = arange(1, 294, 1)

# Constants	[unit]
a_v = 15.5 			# Volume [MeV]
a_s = 16.8 			# Surface [MeV]
a_c = 0.72 			# Coulomb [MeV]
a_sym = 23.0 		# Symmetry [MeV]
a_p = 34.0          # Pairing [MeV]
c2 = 931.494        # c^2 [MeV/u] 
m_H = 1.007825      # Mass of Hydrogen [u]
m_n = 1.008665      # Mass of Neutron [u]

# Z minimum (equation 3.30)
#def Zmin(A):
#	return (m_n - m_H + a_c*A**(-1.0/3.0) + 4.0*a_sym)/(2.0*a_c*A**(-1.0/3.0) + 8.0*a_sym*A**(-1.0))

# Z minimum (equation 3.31)
def Zmin(A):
	return A/(2*(1 + 0.25*A**(2.0/3.0)*(a_c/a_sym)))

# Choosing number of terms to plot
def terms(n):
	Z = Zmin(A)
	if n == 1: # Volume term
		return a_v*A
	elif n == 2: # Volume term + Surface term
		return a_v*A - a_s*A**(2.0/3.0) 
	elif n == 3: # Volume term + Surface term + Coulomb term
		return a_v*A - a_s*A**(2.0/3.0) - a_c*(Z*(Z-1))/A**(1.0/3.0)
	elif n == 4: # Volume term + Surface term + Coulomb term + Symmetry term
		return a_v*A - a_s*A**(2.0/3.0) - a_c*(Z*(Z-1))/A**(1.0/3.0) - a_sym*((A-2*Z)**2)/A

# Plotting the various terms in the semi-empirical mass formula
fig1 = figure(1)
plot(A, terms(1)/A, "r-") 	# Volume term
plot(A, terms(2)/A, "g-") 	# Volume term + Surface term
plot(A, terms(3)/A, "b-") 	# Volume term + Surface term + Coulomb term
plot(A, terms(4)/A, "k-") 	# Volume term + Surface term + Coulomb term + Symmetry term
title("B/A vs. A", fontsize=20)
xlabel("Mass number, A", fontsize=16)
ylabel(r"B(Z$_{min}$, A)/A", fontsize=16)
legend(["Volume", "Volume + Surface", "Volume + Surface + Coulomb", "Volume + Surface + Coulomb + Symmetry"], loc=0)
tick_params(labelsize=14)
fig1.set_tight_layout(True) # Minimizing overlap of labels
savefig("BE1.png") # Saving png
show()



# Binding energy per nucleon with real data

data = "mass16.txt" # Datafile: https://www-nds.iaea.org/amdc/ame2016/mass16.txt

num = 3475-39	# Number of nuclides in datafile
a = zeros(num) 	# Mass number
b = zeros(num)	# Binding energy per nucleon [MeV]

with open(data, "r") as datafile:
	# Skip the first 39 lines in datafile
	for i in xrange(39):
		datafile.readline()
	# Do analysis for the rest of the lines in datafile
	j = 0
	for line in datafile:
		a[j] = float(line[16:19].strip())
		b[j] = float(line[54:63].replace('#', ' ').strip())/1e3 	# keV to MeV
		j += 1

# Plot the real data together with te calculated binding energy
fig2 = figure(2)
plot(a, b, "yx") 			# Real data
plot(A, terms(1)/A, "r-") 	# Volume term
plot(A, terms(2)/A, "g-") 	# Volume term + Surface term
plot(A, terms(3)/A, "b-") 	# Volume term + Surface term + Coulomb term
plot(A, terms(4)/A, "k-") 	# Volume term + Surface term + Coulomb term + Symmetry term
title("B/A vs. A", fontsize=20)
xlabel("Mass number, A", fontsize=16)
ylabel(r"B(Z$_{min}$, A)/A", fontsize=16)
legend(["Data", "Volume", "Volume + Surface", "Volume + Surface + Coulomb", "Volume + Surface + Coulomb + Symmetry"], loc=0)
tick_params(labelsize=14)
fig2.set_tight_layout(True) # Minimizing overlap of labels
savefig("BE2.png") # Saving png
show()

