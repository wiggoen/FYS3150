
from matplotlib.pyplot import *
from numpy import *

# Choose A

A = 128

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
z = arange(46, 62, 1)
mass = [M(i, A) for i in z]
m = array(mass) 

fig = figure(1)
plot(z[::2], m[::2], "ko--", z[1::2], m[1::2], "ro--")

# Writing labels on each point
element = [r'$_{46}$Pd', r'$_{47}$Ag', r'$_{48}$Cd', r'$_{49}$In', r'$_{50}$Sn', 
           r'$_{51}$Sb', r'$_{52}$Te', r'$_{53}$I', r'$_{54}$Xe', r'$_{55}$Cs', 
           r'$_{56}$Ba', r'$_{57}$La', r'$_{58}$Ce', r'$_{59}$Pr', r'$_{60}$Nd', 
           r'$_{61}$Pm']
# Horisontal and vertical offset of labels
hoffsetts = [-15, 22, -20, 22, -20, 22, -15, 2, 3, -2, 15, -10, 15, -15, 15, -20] 
voffsetts = [-20, -12, -10, -12, -10, -5, -17, 7, -20, 5, -15, 7, -15, 2, -15, -5]

for element, Z, M, hoffsetts, voffsetts in zip(element, z, m, hoffsetts, voffsetts):
    annotate(element, xy=(Z, M), xytext=(hoffsetts, voffsetts), ha='center', va='bottom', 
             textcoords='offset points', fontsize=14)

# Uncomment if you want Beta-decay arrows
"""
# Beta-decay arrows
plot([49, 50], [127.931437115, 127.921332747], "b-") # Beta^-
plot([56, 57], [127.911065318, 127.917747210], "g-") # Beta^+
plot([52, 53], [127.910510470, 127.909792562], "m-") # BetaBeta^-
annotate('', xy=(49, 127.931437115), xycoords="data", xytext=(50, 127.921332747), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="blue"))
annotate('', xy=(50, 127.921332747), xycoords="data", xytext=(51, 127.916914939), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="blue"))
annotate('', xy=(51, 127.916914939), xycoords="data", xytext=(52, 127.910510470), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="blue"))
annotate('', xy=(52, 127.910510470), xycoords="data", xytext=(53, 127.909792562), 
         textcoords="data", arrowprops=dict(arrowstyle="->", color="green"))
annotate('', xy=(52, 127.910510470), xycoords="data", xytext=(54, 127.907087994), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="magenta"))
annotate('', xy=(53, 127.909792562), xycoords="data", xytext=(54, 127.907087994), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="blue"))
annotate('', xy=(54, 127.907087994), xycoords="data", xytext=(55, 127.910069986), 
         textcoords="data", arrowprops=dict(arrowstyle="->", color="green"))
annotate('', xy=(55, 127.910069986), xycoords="data", xytext=(56, 127.911065318), 
         textcoords="data", arrowprops=dict(arrowstyle="->", color="green"))
annotate('', xy=(56, 127.911065318), xycoords="data", xytext=(57, 127.917747210), 
         textcoords="data", arrowprops=dict(arrowstyle="->", color="green"))
"""

title("A = %g" %A, fontsize=20)
xlabel("Proton number, Z", fontsize=16)
ylabel("Mass [u]", fontsize=16)
legend(["even Z (and N)", "odd Z (and N)", r"$\beta^-$-decay", r"$\beta^+$-decay", r"$\beta\beta^+$-decay"], loc=0)
tick_params(labelsize=14)
ax = gca()
ax.get_yaxis().get_major_formatter().set_useOffset(False) # Preventing offset of y-axis
fig.set_tight_layout(True)
axis((44.8, 61.7, 127.9, 127.97))
savefig("2d-A%g.png" %A)
show()
