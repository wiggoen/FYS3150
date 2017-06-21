# Proposed solution is written in Python 3.6.1.
# Separation energy

from matplotlib.pyplot import *
from numpy import *

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

# Neutron separation energy
def Sn(Z, A):
	return (M(Z, A-1) - M(Z, A) + m_n)*c2

# Proton separation energy
def Sp(Z, A):
	return (M(Z-1, A-1) - M(Z, A) + m_H)*c2


# Test 1: O-16
print("O-16: Sn = %g MeV, Sp = %g MeV" % (Sn(8, 16), Sp(8, 16)))

