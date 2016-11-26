from pylab import *

billOfAbundance = "noEqualityForFatCats_c_L0.txt"

agents = 500
m0 = 1.0
beta = 1.0/m0
numbins = agents/10
normalized = 1          # 0: not normalized, 1: normalized 

# Load output file
m = loadtxt("outputs/"+billOfAbundance)
#print max(m)
omega_m = beta * exp(-beta * m)
#delta_m = 0.01
#print sum(m)#/agents #= m0


# Histogram with Gibbs distribution
fig1 = figure(1)
grid(True)
if normalized == 0:
    hist(m, bins=numbins, normed=False) # Not normed
    ylabel("Number of agents", fontsize = 16)  # When not normed
if normalized == 1:
    hist(m, bins=numbins, normed=True, label=r"$P(m)$") # Normed
    hold("on")
    plot(m, omega_m, "-r", label=r"$\omega_m$")
    legend(loc=0)
    ylabel(r"Probability density, $P(m)$", fontsize = 16)  # When normed
xlabel(r"Money, $m$", fontsize = 16)
tick_params(labelsize=14)
fig1.set_tight_layout(True)
if normalized == 0:
    savefig("plots/histogram_not_normed.png") # When not normed
if normalized == 1:
    savefig("plots/histogram_normed.png") # When normed
show()

if normalized == 1:
    # log(omega_m)
    fig2 = figure(2)
    semilogy(m, omega_m)
    legend([r"$\log(m)$"], loc=0)
    xlabel(r"Money, $m$", fontsize = 16)
    ylabel(r"$\log(m)$", fontsize = 16)  
    tick_params(labelsize=14)
    fig2.set_tight_layout(True)
    savefig("plots/logOfomega_m.png")
    show()

