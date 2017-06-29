# Proposed solution is written in Python 3.6.1.
# Radius

from matplotlib.pyplot import *
from numpy import *

# Constants	[unit]
R0 = 1.25 # [fm]

# Range of mass number
A = arange(1, 294, 1)

# Radius
R = R0*A**(1.0/3.0)


# Plot of radius
fig1 = figure(1)
plot(A, R)
title("Nuclear radius", fontsize=20)
xlabel("Neutron number, N", fontsize=16)
ylabel("Radius [fm]", fontsize=16)
tick_params(labelsize=14)
fig1.set_tight_layout(True) # Minimizing overlap of labels
savefig("plots/Radius.png") # Saving figure to .png
show()

