from matplotlib.pyplot import *
from numpy import *

# Choose A

A = 135

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

# Plot mass parabola
z = arange(49, 66, 1)
mass = [M(i, A) for i in z]
m = array(mass) 

fig = figure(1)
plot(z, m, "ko-")
title("A = %g" %A, fontsize=20)
xlabel("Proton number, Z", fontsize=16)
ylabel("Mass [u]", fontsize=16)
tick_params(labelsize=14)
ax = gca()
ax.get_yaxis().get_major_formatter().set_useOffset(False) # Preventing offset of y-axis

# Writing labels on each point
element = [r'$_{49}$In', r'$_{50}$Sn', r'$_{51}$Sb', r'$_{52}$Te', r'$_{53}$I', 
           r'$_{54}$Xe', r'$_{55}$Cs', r'$_{56}$Ba', r'$_{57}$La', r'$_{58}$Ce', 
           r'$_{59}$Pr', r'$_{60}$Nd', r'$_{61}$Pm', r'$_{62}$Sm', r'$_{63}$Eu', 
           r'$_{64}$Gd', r'$_{65}$Tb']
# Horisontal and vertical offset of labels
hoffsetts = [-10, -20, -20, -20, -20, -20, -15, -5, 3, 10, 15, 15, 15, 15, 15, 15, 15] 
voffsetts = [-20, -10, -10, -10, -10, -15, -17, -20, -20, -17, -15, -15, -15, -15, -15, -15, -15]

for element, Z, M, hoffsetts, voffsetts in zip(element, z, m, hoffsetts, voffsetts):
    annotate(element, xy=(Z, M), xytext=(hoffsetts, voffsetts), ha='center', va='bottom', 
             textcoords='offset points', fontsize=14)
# Left arrow and text
annotate('', xy=(53, 134.933), xycoords="data", xytext=(51, 134.953), 
         textcoords="data", arrowprops=dict(arrowstyle="->", color="blue"))
text(52.2, 134.945, r'$\beta^-$-decay', fontsize=14)

# Right arrow and text
annotate('', xy=(60, 134.933), xycoords="data", xytext=(62, 134.953), 
         textcoords="data", arrowprops=dict(arrowstyle="->", color="green"))
text(58.3, 134.945, r'$\beta^+$-decay', fontsize=14)

fig.set_tight_layout(True)
axis((47.9, 66.3, 134.905, 134.98))
savefig("2d-A%g.png" %A)
show()

