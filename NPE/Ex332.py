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
fig = figure(1)
# Volume term
plot(A, terms(1)/A, "r-")
# Volume term + Surface term
plot(A, terms(2)/A, "g-")
# Volume term + Surface term + Coulomb term
plot(A, terms(3)/A, "b-")
# Volume term + Surface term + Coulomb term + Symmetry term
plot(A, terms(4)/A, "m-")
title("B/A vs. A", fontsize=20)
xlabel("Mass number, A", fontsize=16)
ylabel(r"B(Z$_{min}$, A)/A", fontsize=16)
legend(["Volume", "Volume + Surface", "Volume + Surface + Coulomb", "Volume + Surface + Coulomb + Symmetry"], loc=0)
tick_params(labelsize=14)
fig.set_tight_layout(True) # Minimizing overlap of labels
savefig("ex332.png") # Saving png
show()

