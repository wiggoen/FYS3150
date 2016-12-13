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
        savefig("plots/c_histdist"+L[i]+".png")
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
    savefig("plots/c_subhist.png")
    show()
    return "Done."

subhist()


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
    savefig("plots/c_probdist.png")
    show()
    return "Done."

probdist()


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
    savefig("plots/c_logplot.png")
    show()
    return "Done."

dist()


def Pareto():
    fig = figure()
    for i in range(len(Lambda)):
        m = loadtxt("outputs/noEqualityForFatCats_c_"+L[i]+".txt")
        x = arange(len(m))
        if L[i] == 0:
            P = beta * exp(-beta * m)
        else:
            n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
            a = n**n / gamma(n)
            x = m/m0
            P = a*x**(n-1)*exp(-n*x)
        loglog(m, P, label=r"$\lambda = %g$" %(Lambda[i]))
        hold("on")
        if i == 0:
            start = 20
            fract = 0.5
            loglog(1.25*m[50:len(m)*fract], (m**(-1-13))[50:len(m)*fract], "--", label=r"$P_\alpha = 13$")
            loglog(1.6*m[start:len(m)*fract], (m**(-1-7))[start:len(m)*fract], "--", label=r"$P_\alpha = 7$")
            loglog(1.85*m[start:len(m)*fract], (m**(-1-5.75))[start:len(m)*fract], "--", label=r"$P_\alpha = 5.75$")
            loglog(2*m[0:len(m)*fract], (m**(-1-4.5))[0:len(m)*fract], "--", label=r"$P_\alpha = 4.5$")
        art = []
        lgd = legend(bbox_to_anchor=(0.0, 1.01, 1., 0.102), loc=3, ncol=4, mode="expand", borderaxespad=0.0)
        xlabel(r"$m$", fontsize = 16)
        ylabel(r"$P_n(x)$", fontsize = 16) 
        tick_params(labelsize=14)
        fig.set_tight_layout(True)
        savefig("plots/c_Pareto.png", additional_artists=art, bbox_inches="tight")
    show()
    return "Done."

Pareto()

