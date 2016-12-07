from pylab import *
from scipy.special import *

Lambda = [0, 0.25, 0.5, 0.9]
L = ["L0", "L025", "L05", "L09"]
m0 = 1.0
beta = 1.0/m0


def histdist():
    agents = 500
    numbins = 500/10
    for i in range(len(Lambda)):
        fig = figure()
        m = loadtxt("outputs/noEqualityForFatCats_c_"+L[i]+".txt")
        hist(m, bins=numbins, normed=True, label=r"$P(m), \lambda = %g$" %Lambda[i]) 
        hold("on")
        n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
        a = n**n / gamma(n)
        x = m/m0
        #x = m_/m0/n
        P = a*x**(n-1)*exp(-n*x)
        #P = x**(n-1)*exp(-x)/gamma(n)
        plot(m, P, "-r", label=r"$\omega_m$")
        legend(loc=0)
        xlabel(r"Money, $m$", fontsize = 16)
        ylabel(r"Probability density, $P(m)$", fontsize = 16) 
        tick_params(labelsize=14)
        fig.set_tight_layout(True)
        savefig("plots/histdist"+L[i]+".png")
        show()
    return "Done."

histdist()

# 4 subplots of histograms
def subhist():
    fig = figure(1)
    agents = 500
    numbins = 500/10
    for i in range(len(Lambda)):
        num = 221+i
        subplot(num)
        m = loadtxt("outputs/noEqualityForFatCats_c_"+L[i]+".txt")
        hist(m, bins=numbins, normed=True, label=r"$\lambda = %g$" %Lambda[i]) 
        hold("on")
        n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
        a = n**n / gamma(n)
        x = m/m0
        #x = m_/m0/n
        P = a*x**(n-1)*exp(-n*x)
        #P = x**(n-1)*exp(-x)/gamma(n)
        plot(m, P, "-r", label=r"$\omega_m$")
        if i == 0 or i == 2:
            ylabel(r"$P(m)$", fontsize = 16) 
        if i == 2 or i == 3:
            xlabel(r"$m$", fontsize = 16)
        legend(loc=0)
        tick_params(labelsize=14)
    fig.set_tight_layout(True)
    savefig("plots/subhist.png")
    show()
    return "Done."

subhist()


def dist():
    fig = figure()
    for i in range(len(Lambda)):
        m = loadtxt("outputs/noEqualityForFatCats_c_"+L[i]+".txt")
        if L[i] == 0:
            P = beta * exp(-beta * m) # omega_m
        else:
            n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
            a = n**n / gamma(n)
            x = m/m0
            #x = m/m0/n
            P = a*x**(n-1)*exp(-n*x)
            #P = x**(n-1)*exp(-x)/gamma(n)
        loglog(m, P)
        hold("on")
    legend([r"$\lambda = 0$", r"$\lambda = 0.25$", r"$\lambda = 0.5$", r"$\lambda = 0.9$"], loc=3)
    xlabel(r"Money, $m$", fontsize = 16)
    ylabel(r"Probability density, $P(m)$", fontsize = 16) 
    tick_params(labelsize=14)
    fig.set_tight_layout(True)
    savefig("plots/logplot.png")
    show()
    return "Done."

dist()
