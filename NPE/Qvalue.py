# Proposed solution is written in Python 3.6.1.
# Q-value

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
m_e = 5.485799e-4 	# Mass of Electron [u]

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

# Calculate Q-value (equation 8.8)
def Qalpha(Z, A): 
	return (M(Z, A) - M(Z-2, A-4) - M(2, 4))*c2
	#return B(2, 4) + B(Z-2, A-4) - B(Z, A)

def Qelectron(Z, A):
	return (M(Z, A) - M(Z+1, A))*c2

def Qpositron(Z, A):
	return (M(Z, A) - M(Z-1, A) - 2*m_e)*c2

def QelectronCapture(Z, A):
	return (M(Z, A) - M(Z-1, A))*c2 - BE(n) 	# BE(n) is the binding energy of the captured n-shell electron


# Geiger-Nuttall rule
# log(t_halflife) \propto 1/sqrt(Qalpha)


# Alpha-decay
print("Th-218: calculated = %g, book-value = ?.?? MeV, measured = %g MeV" % (Qalpha(90, 218), 9.85)) # Th-218
print("Th-220: calculated = %g, book-value = %g MeV, measured = %g MeV" % (Qalpha(90, 220), 7.77, 8.95)) # Th-220
print("Th-226: calculated = %g, book-value = %g MeV, measured = %g MeV" % (Qalpha(90, 226), 6.75, 6.45)) # Th-226
print("Th-232: calculated = %g, book-value = %g MeV, measured = %g MeV" % (Qalpha(90, 232), 5.71, 4.08)) # Th-232

# Beta-decay
print("Bi-210 (b-): calculated = %g, book-value = %g MeV" % (Qelectron(83, 210), 1.161)) 	# Bi-210
print(" I-124 (b+): calculated = %g, book-value = %g MeV" % (Qpositron(53, 124), 2.14)) 	# I-124
#print("Ca-41 (ec): calculated = %g, book-value = %g MeV, measured = ? MeV" % (QelectronCapture(20, 41), 0.43)) # Ca-41
