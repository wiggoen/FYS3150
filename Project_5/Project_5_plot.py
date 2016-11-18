from pylab import *
"""
x = linspace(0,500,501)
y = exp(-0.0123 * x)
semilogy(x,y)
show()
"""

billOfAbundance = "noEqualityForFatCats.txt"

# Load output file
m = loadtxt("outputs/"+billOfAbundance)
Delta_m = 50 # Number of bins

# Histogram
fig1 = figure(1)
#hist(source, bins=Delta_m, normed=1, facecolor='blue', alpha=0.75, label="m")
hist(m, bins=Delta_m, facecolor='blue', label="m")
#xticks(rotation='vertical')
grid(True)
art = []
lgd = legend(loc="upper left", bbox_to_anchor=(1, 1))
xlabel("m", fontsize = 16)
ylabel(r"Probability, $P(m)$", fontsize = 16)  
tick_params(labelsize=14)
fig1.set_tight_layout(True)

savefig("plots/Histogram.png", additional_artists=art, bbox_inches="tight")
show()


# Plot of log(m)
fig2 = figure(2)
t = arange(len(m))
semilogy(t, m)
#grid(True)
art = []
lgd = legend(r"$\log(m)$", loc="upper left", bbox_to_anchor=(1, 1))
xlabel(r"$Agents$", fontsize = 16)
ylabel(r"$\log(m)$", fontsize = 16)  
tick_params(labelsize=14)
fig1.set_tight_layout(True)

savefig("plots/logOfm.png", additional_artists=art, bbox_inches="tight")
show()
