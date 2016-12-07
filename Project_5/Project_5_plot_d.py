from pylab import *
from scipy.special import *

N = [500, 1000]
Lambda = [0, 0.25]
L = ["L0", "L025"]
Alpha = [0.5, 1.0, 1.5, 2.0]
A = ["a05", "a1", "a15", "a2"]
m0 = 1.0
beta = 1.0/m0

def dist():
    fig = figure()
    for k in range(len(N)):
        for i in range(len(Lambda)):
            for j in range(len(Alpha)): 
                m = loadtxt("outputs/noEqualityForFatCats_N"+str(N[k])+"_"+L[i]+"_"+A[j]+".txt")
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
                #semilogx(m, P)
                #semilogy(m, P)
                #plot(m, P)
                #legend([r"$\lambda = 0$", r"$\lambda = 0.25$", r"$\lambda = 0.5$", r"$\lambda = 0.9$"], loc=3)
                
                legend([r"$N = %g, \lambda = %g, \alpha = %g$" %(N[k], Lambda[i], Alpha[j])])#, loc=3)    
                hold("on")
    xlabel(r"Money, $m$", fontsize = 16)
    ylabel(r"$P(m)$", fontsize = 16) 
    tick_params(labelsize=14)
    fig.set_tight_layout(True)
    #savefig("plots/logplot_orwhat.png")
    show()
    return "Done."

dist()



"""
def histdist():
    for k in range(len(N)):
        #agents = N[k]
        numbins = N[k]/10
        for j in range(len(Alpha)):
            for i in range(len(Lambda)):
                fig = figure()
                m = loadtxt("outputs/noEqualityForFatCats_N"+str(N[k])+"_"+L[i]+"_"+A[j]+".txt")
                hist(m, bins=numbins, normed=True, label=r"$P(m), \lambda = %g$" %Lambda[i]) 
                hold("on")
                n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
                a = n**n / gamma(n)
                x = m/m0
                #x = m_/m0/n
                P = a*x**(n-1)*exp(-n*x)
                #P = x**(n-1)*exp(-x)/gamma(n)
                plot(m, P, "-r", label=r"$\omega_m$")
                legend(loc=0)  # [r"$\omega_m$", r"$P(m), \lambda = %g$" %Lambda[i]], 
                xlabel(r"Money, $m$", fontsize = 16)
                ylabel(r"Probability density, $P(m)$", fontsize = 16) 
                tick_params(labelsize=14)
                fig.set_tight_layout(True)
                #savefig("plots/histdist_orwhat"+L[i]+".png")
                show()
            return "Done."

histdist()
"""

