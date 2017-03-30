from matplotlib.pyplot import *
from numpy import *

# Choose element

A = 163
Z = 68

# Constants
a_v = 15.5          # MeV
a_s = 16.8          # MeV
a_c = 0.72          # MeV
a_sym = 23.0        # MeV
a_p = 34.0          # MeV
c2 = 931.502        # (c**2) MeV/u 
m_H = 1.007825      # u
m_n = 1.008665      # u

def N(Z, A):
    return A-Z

def delta(Z, A):
    if (Z % 2 == 0 and N(Z, A) % 2 == 0):
        return 1
    elif (Z % 2 == 1 and N(Z, A) % 2 == 1):
        return -1
    else:
        return 0

def B(Z, A):
    return a_v*A - a_s*A**(2.0/3.0) - a_c*(Z*(Z-1))/A**(1.0/3.0) - a_sym*((A-2*Z)**2)/A + delta(Z, A)*a_p/A**(3.0/4.0)

def M(Z, A):
    return Z*m_H + N(Z, A)*m_n - B(Z, A)/c2

print("For Z = %g and A = %g, the mass is %.6f u" % (Z, A, M(Z, A)))

