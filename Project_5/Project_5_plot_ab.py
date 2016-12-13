from pylab import *

billOfAbundance = "noEqualityForFatCats_c_L0.txt"

agents = 500
m0 = 1.0
beta = 1.0/m0
numbins = agents/10
normalized = 1          # 0: not normalized, 1: normalized 

# Load output file
m = loadtxt("outputs/"+billOfAbundance)
omega_m = beta * exp(-beta * m)

# Histogram with Gibbs distribution
fig1 = figure(1)
grid(True)
if normalized == 0:
    hist(m, bins=numbins, normed=False, label="Agents") # Not normed
    legend(loc=0)
    ylabel("Agents", fontsize = 16)  # When not normed
if normalized == 1:
    hist(m, bins=numbins, normed=True, label=r"$P(m)$") # Normed
    hold("on")
    plot(m, omega_m, "-r", label=r"$\omega_m$")
    legend(loc=0)
    ylabel(r"Probability density, $P(m)$", fontsize = 16)  # When normed
xlabel(r"$m$", fontsize = 16)
tick_params(labelsize=14)
fig1.set_tight_layout(True)
if normalized == 0:
    savefig("plots/a_histogram_not_normed.png") # When not normed
if normalized == 1:
    savefig("plots/a_histogram_normed.png") # When normed
show()

# Plot of log(omega_m)
if normalized == 1:
    fig2 = figure(2)
    semilogy(m, omega_m)
    legend([r"$\log(\omega_m)$"], loc=0)
    xlabel(r"$m$", fontsize = 16)
    ylabel(r"$\log(\omega_m)$", fontsize = 16)  
    tick_params(labelsize=14)
    fig2.set_tight_layout(True)
    savefig("plots/b_logOfomega_m.png")
    show()
