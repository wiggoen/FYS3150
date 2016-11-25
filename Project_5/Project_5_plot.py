from pylab import *
from scipy import *

billOfAbundance = "noEqualityForFatCats_c_L0.txt"

agents = 500
m0 = 1.0
beta = 1.0/m0
numbins = agents/10

# Load output file
m = loadtxt("outputs/"+billOfAbundance)
#print max(m)
omega_m = beta * exp(-beta * m)
#delta_m = 0.01
print sum(m)#/agents #= m0


# Histogram with Gibbs distribution
fig1 = figure(1)
hist(m, bins=numbins, normed=True, label=r"$P(m)$")#, weights=omega_m*delta_m)
grid(True)
hold("on")
plot(m, omega_m, "-r", label=r"$\omega_m$")
art = []
lgd = legend(loc="upper left", bbox_to_anchor=(1, 1))
xlabel(r"Money, $m$", fontsize = 16)
#ylabel("Number of agents", fontsize = 16)  # When not normed
ylabel(r"Probability density, $P(m)$", fontsize = 16)  # When normed
tick_params(labelsize=14)
fig1.set_tight_layout(True)
savefig("plots/histogram.png", additional_artists=art, bbox_inches="tight")
show()


# log(omega_m)
fig2 = figure(2)
semilogy(m, omega_m)
art = []
lgd = legend([r"$\log(m)$"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel(r"Money, $m$", fontsize = 16)
ylabel(r"$\log(m)$", fontsize = 16)  
tick_params(labelsize=14)
fig2.set_tight_layout(True)
savefig("plots/logOfomega_m.png", additional_artists=art, bbox_inches="tight")
show()


# omega_m
fig3 = figure(3)
plot(m, omega_m, "-b")#, m, m**(-2), "-r")
art = []
lgd = legend([r"$\lambda = 0$"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel(r"Money, $m$", fontsize = 16)
ylabel(r"$\omega_m$", fontsize = 16)  
tick_params(labelsize=14)
fig3.set_tight_layout(True)
savefig("plots/omega_m.png", additional_artists=art, bbox_inches="tight")
show()
