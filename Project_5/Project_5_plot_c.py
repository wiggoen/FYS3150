from pylab import *
from scipy import *

Lambda = [0, 0.25, 0.5, 0.9]
L = ["L0", "L025", "L05", "L09"]
m0 = 1.0
beta = 1.0/m0

fig = figure()
for i in range(len(Lambda)):
    m = loadtxt("outputs/noEqualityForFatCats_c_"+L[i]+".txt")
    if L[i] == 0:
        P = beta * exp(-beta * m) # omega_m
        loglog(m, P)
    else:
        n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
        a = n**n / gamma(n)
        x = m/m0
        P = a*x**(n-1)*exp(-n*x)
        loglog(m, P)
    hold("on")
art = []
lgd = legend([r"$\lambda = 0$", r"$\lambda = 0.25$", r"$\lambda = 0.5$", r"$\lambda = 0.9$"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel(r"Money, $m$", fontsize = 16)
ylabel(r"Probability density, $P(m)$", fontsize = 16) 
tick_params(labelsize=14)
fig.set_tight_layout(True)
savefig("plots/logplot.png", additional_artists=art, bbox_inches="tight")
show()

