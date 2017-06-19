# Proposed solution is written in Python 3.6.1.
# Mass parabola

from matplotlib.pyplot import *
from numpy import *

# Choose A, Zmin and Zmax
#A = 125
#Zmin = 45
#Zmax = 60

A = 128
Zmin = 46
Zmax = 61

# Constants	[unit]
a_v = 15.5 			# Volume [MeV]
a_s = 16.8 			# Surface [MeV]
a_c = 0.72 			# Coulomb [MeV]
a_sym = 23.0 		# Symmetry [MeV]
a_p = 34.0          # Pairing [MeV]
c2 = 931.494        # c^2 [MeV/u] 
m_H = 1.007825      # Mass of Hydrogen [u]
m_n = 1.008665      # Mass of Neutron [u]

# Neutron number
def N(Z, A):
	return A-Z

# Delta factor from pairing term
def delta(Z, A):
	# If both Z and N is even
	if (Z % 2 == 0 and N(Z, A) % 2 == 0): 
		return 1
		# If both Z and N is odd
	elif (Z % 2 == 1 and N(Z, A) % 2 == 1): 
		return -1
    # If A is odd
	else: 
		return 0

# Complete binding energy (equation 3.28)
def B(Z, A):
	return a_v*A - a_s*A**(2.0/3.0) - a_c*(Z*(Z-1))/A**(1.0/3.0) - a_sym*((A-2*Z)**2)/A + delta(Z, A)*a_p/A**(3.0/4.0)

# Semi-empirical mass formula (SEMF) (equation 3.29)
def M(Z, A):
	return Z*m_H + N(Z, A)*m_n - B(Z, A)/c2

# Calculate mass parabola
z = arange(Zmin, Zmax, 1)
mass = [M(i, A) for i in z]
m = array(mass) 

# Plot mass parabola
fig = figure(1)
if (A % 2 == 1): # Plot for odd A 
	plot(z, m, "ko--", z[argmin(m)], min(m), "go")
	legend(["odd A", "Most bound"], loc=0)
else: # Plot for even Z and N, and odd Z and N
	plot(z[::2], m[::2], "bo--", z[1::2], m[1::2], "ro--", z[argmin(m)], min(m), "go")
	legend(["even Z (and N)", "odd Z (and N)", "Most bound"], loc=0)
title("A = %g" %A, fontsize=20)
xlabel("Proton number, Z", fontsize=16)
ylabel("Mass [u]", fontsize=16)
tick_params(labelsize=14)
ax = gca()
ax.get_yaxis().get_major_formatter().set_useOffset(False) # Preventing offset of y-axis
fig.set_tight_layout(True) # Minimizing overlap of labels
axis((Zmin-0.5, Zmax+0.5, min(m)-0.005, max(m)+0.005)) # Setting axis ranges
savefig("ex331_A%g.png" %A) # Saving png
show()

