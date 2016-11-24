from pylab import *

billOfAbundance = "noEqualityForFatCats.txt"

m0 = 1e5
runs = 1e4
beta = 1.0/m0

norm = 1.0/runs # remove norm when output is normalized

agents = 500
numbins = 2*runs/agents

# Load output file
m = loadtxt("outputs/"+billOfAbundance) * norm # remove norm when output is normalized
omega_m = beta * exp(-beta*m)


# Histogram with Gibbs distribution
fig1 = figure(1)
hist(m, bins=numbins, normed=True, facecolor='blue', label=r"$P(m)$")
grid(True)
hold("on")
plot(m, omega_m, "-r", label=r"$\omega_m$")
art = []
lgd = legend(loc="upper left", bbox_to_anchor=(1, 1))
xlabel(r"Money, $m$", fontsize = 16)
ylabel(r"Probability, $P(m)$", fontsize = 16)  
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
