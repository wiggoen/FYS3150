from pylab import *

billOfAbundance = "noEqualityForFatCats_onerun.txt"

runs = 1e2
agents = 500
m0 = 1.0
print m0
beta = 1.0/m0
print beta 
numbins = agents/10

# Load output file
m = loadtxt("outputs/"+billOfAbundance)

omega_m = beta * exp(-beta * m)
print sum(m)#/agents

# Histogram with Gibbs distribution
fig1 = figure(1)
hist(m, bins=numbins, normed=True, facecolor='blue', label=r"$\omega_m$")
grid(True)
hold("on")
plot(m, omega_m, "-r", label=r"$\omega_m$")
art = []
lgd = legend(loc="upper left", bbox_to_anchor=(1, 1))
xlabel(r"Money, $m$", fontsize = 16)
ylabel("Number of agents", fontsize = 16)  
#ylabel(r"Probability, $P(m)$", fontsize = 16)  
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
