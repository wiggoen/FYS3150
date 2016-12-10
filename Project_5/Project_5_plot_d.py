from pylab import *
from scipy.special import *
import matplotlib.pyplot as plt

N = [500, 1000]
Lambda = [0, 0.25]
L = ["L0", "L025"]
Alpha = [0.5, 1.0, 1.5, 2.0]
A = ["a05", "a1", "a15", "a2"]
#m0 = 1.0
#beta = 1.0/m0

def dist():
    #fig = figure()
    for k in range(len(N)):
        fig = figure(k+1)
        for i in range(len(Lambda)):
            num = 121+i
            subplot(num)
            for j in range(len(Alpha)):
                m = loadtxt("outputs/noEqualityForFatCats_N"+str(N[k])+"_"+L[i]+"_"+A[j]+".txt")
                M = sum(m)
                #print "M = ", M
                T = M/N[k]
                #print "T = ", T
                #P = (1.0/T) * exp(-m/T) # same as omega_m
                
                data, binEdges = np.histogram(m, bins=30)
                bincenters = 0.5*(binEdges[1:]+binEdges[:-1]) #Center bin data
                #bincenters = bincenters * n / 100. #Rescale bincenters
                dbins = bincenters[1]-bincenters[0] #Width of bins
                print dbins
                loglog(bincenters, data/(float(N[k])), label=r'$i$')

                #else:
                #    n = 1.0 + ((3.0*Lambda[i])/(1.0-Lambda[i]))
                #    a = n**n / gamma(n)
                #    x = m/m0
                #    P = a*x**(n-1)*exp(-n*x)
                #loglog(m, P, label=r"$N = %g, \lambda = %g, \alpha = %g$" %(N[k], Lambda[i], Alpha[j]))
                #x = arange(len(m))
                #hist(m, bins = 10 ** np.linspace(np.log10(min(m)), np.log10(max(m)), 20), log=True)
                #gca().set_xscale("log")
                """
                vals = plt.hist(m, bins=logspace(log10(min(m)), log10(max(m)), 30))
                bins = vals[1][:-1]
                vals = vals[0]
                plt.figure(10)
                plt.loglog(bins, vals)
                """
                #loglog(m, x, label=r"$\alpha = %g$" %(Alpha[j])) # ($N = %g, \lambda = %g) %(N[k], Lambda[i])
                #semilogx(m, P)
                #semilogy(m, P)
                #plot(m, P)
                #legend([r"$\lambda = 0$", r"$\lambda = 0.25$", r"$\lambda = 0.5$", r"$\lambda = 0.9$"], loc=3)
                hold("on")
                
            legend(loc=0)
            title(r"$N = %g, \lambda = %g$" %(N[k], Lambda[i])) 
            xlabel(r"$m$", fontsize = 16)
            ylabel("arange(len(m))", fontsize = 16)  #r"$P_{GB}(m)$"
            tick_params(labelsize=14)
            fig.set_tight_layout(True)
            #savefig("plots/test_"+str(k+1)+".png")
                
    #legend([r"$N = %g, \lambda = %g, \alpha = %g$" %(N[k], Lambda[i], Alpha[j])])#, loc=3)    
    
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

