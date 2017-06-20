# Proposed solution is written in Python 3.6.1.
# Radioactive decay

from matplotlib.pyplot import *
from numpy import *

N0 = 1e5
Lambda = log(2)/30.05  	# [1/y]

t = linspace(0, 100, 10000)   	# Time interval [s]
N = N0*exp(-Lambda*t) 			# Number of nuclei not decayed
A = Lambda*N 					# Activity [Bq]


fig = figure(1)

subplot(221)
plot(t, N, "b-")
title("Radioactive decay", fontsize=20)
xlabel("time [y]", fontsize=16)
ylabel("N(t)", fontsize=16)
legend(["Cs-137"], loc=0)
tick_params(labelsize=14)

subplot(222)
plot(t, A, "r-")
title("Activity", fontsize=20)
xlabel("time [y]", fontsize=16)
ylabel("A(t)", fontsize=16)
legend(["Cs-137"], loc=0)
tick_params(labelsize=14)

subplot(223)
semilogy(t, N, "b-")
xlabel("time [y]", fontsize=16)
ylabel("ln(N(t))", fontsize=16)
legend(["Cs-137"], loc=0)
tick_params(labelsize=14)

subplot(224)
semilogy(t, A, "r-")
xlabel("time [y]", fontsize=16)
ylabel("ln(A(t))", fontsize=16)
legend(["Cs-137"], loc=0)
tick_params(labelsize=14)

fig.set_tight_layout(True) # Minimizing overlap of labels
savefig("RD.png") # Saving figure to .png
show()