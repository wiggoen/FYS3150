from pylab import *
import numpy as np
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
        P = a*x**(n-1)*exp(-n*x)
        if i == 0:
            plot(m, P, "-r", label=r"$\omega_m$")
        else:
            plot(m, P, "-r", label=r"$P_n(x)$")
        legend(loc=0)
        xlabel(r"$m$", fontsize = 16)
        ylabel(r"$P(m)$", fontsize = 16) 
        tick_params(labelsize=14)
        fig.set_tight_layout(True)
        savefig("plots/histdist"+L[i]+".png")
        show()
    return "Done."

#histdist()

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
        P = a*x**(n-1)*exp(-n*x)
        if i == 0:
            plot(m, P, "-r", label=r"$\omega_m$")
        else:
            plot(m, P, "-r", label=r"$P_n(x)$")
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

#subhist()

def probdist():
    agents = 500
    numbins = 500/10
    fig = figure()
    for i in range(len(Lambda)):
        m = loadtxt("outputs/noEqualityForFatCats_c_"+L[i]+".txt")
        n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
        a = n**n / gamma(n)
        x = m/m0
        P = a*x**(n-1)*exp(-n*x) / 20 
        if i == 0:
            plot(m, P, label=r"$\lambda = 0$")
        else:
            plot(m, P, label=r"$\lambda = %g$" %Lambda[i])
        hold("on")

    legend(loc=0)
    xlabel(r"$m$", fontsize = 16)
    ylabel(r"$P_n(x)$", fontsize = 16) 
    tick_params(labelsize=14)
    fig.set_tight_layout(True)
    savefig("plots/probdist.png")
    show()
    return "Done."

#probdist()


def dist():
    fig = figure()
    for i in range(len(Lambda)):
        m = loadtxt("outputs/noEqualityForFatCats_c_"+L[i]+".txt")
        if L[i] == 0:
            P = beta * exp(-beta * m) / 20 # omega_m
        else:
            n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
            a = n**n / gamma(n)
            x = m/m0
            P = a*x**(n-1)*exp(-n*x) / 20
        loglog(m, P)
        hold("on")
    legend([r"$\lambda = 0$", r"$\lambda = 0.25$", r"$\lambda = 0.5$", r"$\lambda = 0.9$"], loc=3)
    xlabel(r"$m$", fontsize = 16)
    ylabel(r"$P_n(x)$", fontsize = 16) 
    tick_params(labelsize=14)
    fig.set_tight_layout(True)
    savefig("plots/logplot.png")
    show()
    return "Done."

#dist()

binsize = 20
#N1=int(max(m1)/binsize)
#N2=int(max(m2)/binsize)
#N3=int(max(m3)/binsize)
#N4=int(max(m4)/binsize)

def tails():
    N = 500
    fig = figure()
    #d = loadtxt("outputs/noEqualityForFatCats_N1000_L0_a2_g1.txt")
    m = loadtxt("outputs/noEqualityForFatCats_c_"+L[3]+".txt")
    #numbins = int(max(m)*50/binsize)
    numbins = 20
    #print numbins
    #K = int(max(m)/binsize)
    #print K
    #print max(m)
    #print mean(m)
    data, bin_edges = np.histogram(m, bins=numbins, normed=True)
    print bin_edges
    """
    data, binEdges = np.histogram(m, bins=binsize)
    bincenters = 0.5*(binEdges[1:]+binEdges[:-1]) #Center bin data
    dbins = bincenters[1]-bincenters[0] #Width of bins
    loglog(bincenters, data/(float(N)),label=r'$ \gamma = 0.0$')
    loglog(m)
    """
    plot(data)
    hold("on")
    hist(m, bins=50)
    #loglog(m, label=r"$m$")
    #tail = m[480:]
    #loglog(m, label=r"$m$")
    #hold("on")
    #a = 1
    #b = 1
    #loglog(300000000*m**(3), label=r"$Param$")
    #legend(loc=0)

    #savefig("plots/tails.png")
    show()
    return "Done."

tails()
"""
n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
a = n**n / gamma(n)
x = m/m0
P = a*x**(n-1)*exp(-n*x) / 20 
if i == 0:
    plot(m, P, label=r"$\lambda = 0$")
else:
    plot(m, P, label=r"$\lambda = %g$" %Lambda[i])
hold("on")
"""
"""
legend(loc=0)
xlabel(r"$m$", fontsize = 16)
ylabel(r"$P_n(x)$", fontsize = 16) 
tick_params(labelsize=14)
fig.set_tight_layout(True)
#savefig("plots/tails.png")
"""





