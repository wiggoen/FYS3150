# Proposed solution is written in Python 3.6.1.
# Radioactive decay

from matplotlib.pyplot import *
from numpy import *

N0 = 1e5
Lambda = log(2)/30.05  	# [1/y]

t = linspace(0, 100, 10000)   	# Time interval [y]
N = N0*exp(-Lambda*t) 			# Number of nuclei not decayed
A = Lambda*N 					# Activity [Bq]


fig1 = figure(1)
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

fig1.set_tight_layout(True) # Minimizing overlap of labels
savefig("RD.png") # Saving figure to .png
#show()


# Radioactive decay chain
T = linspace(0, 1e6, 10000) # Time interval [y]
Lambda1 = log(2)/2.45e5  	# U-234 [1/y]
Lambda2 = log(2)/8.0e4  	# Th-230 [1/y]
Lambda3 = log(2)/10e15  	# Stable [1/y]

# Plot
fig2 = figure(2)
N1 = N0*exp(-Lambda1*T)
N2 = N0*Lambda1*(exp(-Lambda1*T) - exp(-Lambda2*T))/(Lambda2 - Lambda1)
N3 = N0*(Lambda1*(1.0 - exp(-Lambda2*T)) - Lambda2*(1.0 - exp(-Lambda1*T)))/(Lambda1 - Lambda2)

plot(T, N1, T, N2, T, N3)
title("Radioactive decay chain", fontsize=20)
xlabel("time [y]", fontsize=16)
ylabel(r"N$_x$(t)", fontsize=16)
legend([r"N$_1$(t) Parent", r"N$_2$(t) Daughter", r"N$_3$(t) Stable"], loc=0)
tick_params(labelsize=14)
fig2.set_tight_layout(True) # Minimizing overlap of labels
savefig("RDC.png") # Saving figure to .png
show()

