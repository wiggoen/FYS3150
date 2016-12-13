from pylab import *
from scipy.special import *

N = 1000
Lambda = [0, 0.25]
L = ["L0", "L025"]
Alpha = [1.0, 2.0]
A = ["a1", "a2"]
Gamma = [0.0, 1.0, 2.0, 3.0, 4.0]
G = ["g0", "g1", "g2", "g3", "g4"]


def dist():
    for j in range(len(Alpha)):
        fig = figure(j+1)
        for i in range(len(Lambda)):  
            num = 121+i
            subplot(num)
            for k in range(len(Gamma)):
                m = loadtxt("outputs/noEqualityForFatCats_N"+str(N)+"_"+L[i]+"_"+A[j]+"_"+G[k]+".txt") / N            
                loglog(m/sum(m), label=r"$\gamma = %1.1f$" %(Gamma[k]))
                hold("on")
            legend(loc=0)
            title(r"$N = %g, \lambda = %g, \alpha = %g$" %(N, Lambda[i], Alpha[j]), fontsize = 16) 
            xlabel(r"$m$", fontsize = 16)
            ylabel("Probability distribution", fontsize = 16) 
            tick_params(labelsize=14)
            fig.set_tight_layout(True)
            savefig("plots/e_loglog_probdist_"+str(j+1)+".png")
    show()
    return "Done."

dist()


def Pareto():
    for j in range(len(Alpha)):
        fig = figure(j+1)
        for i in range(len(Lambda)):
            num = 121+i
            subplot(num)
            for k in range(len(Gamma)):
                m = loadtxt("outputs/noEqualityForFatCats_N"+str(N)+"_"+L[i]+"_"+A[j]+"_"+G[k]+".txt")
                x = arange(len(m))
                if k == 0:
                    if j == 0:
                        b = 2.65e2
                    else:
                        b = 2.0e2
                    if i == 0:
                        start = 0
                        fract = 0.45
                    else:
                        start = 0
                        fract = 0.45
                    alp = [2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5]
                    for s in range(len(alp)):
                        loglog(b*m[start:len(m)*fract], (m**(-1-alp[s]))[start:len(m)*fract], label=r"$P_\alpha = %1.2f$" %(alp[s]))
                loglog(x, m)
                hold("on")
                #loglog(x[len(m)*0.6:], m[len(m)*0.6:])
                #hold("on")
            art = []
            lgd = legend(bbox_to_anchor=(0.0, 1.06, 1., 0.102), loc=3, ncol=2, mode="expand", borderaxespad=0.0)
            title(r"$N = %g, \lambda = %g, \alpha = %g$" %(N, Lambda[i], Alpha[j]), fontsize = 16)
            xlabel(r"$m$", fontsize = 16)
            ylabel("Probability Distribution", fontsize = 16)
            tick_params(labelsize=14)
            fig.set_tight_layout(True)
            savefig("plots/e_Pareto_"+str(j+1)+".png", additional_artists=art, bbox_inches="tight")
    show()
    return "Done."

Pareto()

