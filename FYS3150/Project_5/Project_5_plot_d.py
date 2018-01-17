from pylab import *
from scipy.special import *

N = [500, 1000] 
Lambda = [0, 0.25]
L = ["L0", "L025"]
Alpha = [0.5, 1.0, 1.5, 2.0]
A = ["a05", "a1", "a15", "a2"]


def dist():
    for k in range(len(N)):
        fig = figure(k+1)
        for i in range(len(Lambda)):
            num = 121+i
            subplot(num)
            for j in range(len(Alpha)):
                m = loadtxt("outputs/noEqualityForFatCats_N"+str(N[k])+"_"+L[i]+"_"+A[j]+".txt") / N[k]
                loglog(m/sum(m), label=r"$\alpha = %1.1f$" %(Alpha[j]))
                hold("on")
            legend(loc=0)
            title(r"$N = %g, \lambda = %g$" %(N[k], Lambda[i]), fontsize = 16) 
            xlabel(r"$m$", fontsize = 16)
            ylabel("Probability Distribution", fontsize = 16)
            tick_params(labelsize=14)
            fig.set_tight_layout(True)
            savefig("plots/d_loglog_probdist_"+str(k+1)+".png")
    show()
    return "Done."

dist()


def Pareto():
    for k in range(len(N)):
        fig = figure(k+1)
        for i in range(len(Lambda)):
            num = 121+i
            subplot(num)
            for j in range(len(Alpha)):
                m = loadtxt("outputs/noEqualityForFatCats_N"+str(N[k])+"_"+L[i]+"_"+A[j]+".txt")
                x = arange(len(m))
                if j == 0:
                    if k == 0:
                        b = 1.45e2
                    else:
                        b = 1.55e2
                    if i == 0:
                        start = 0
                        fract = 0.75
                    else:
                        start = 20
                        fract = 0.9
                    alp = [0.75, 1, 1.25, 1.5, 1.75, 2, 2.25]
                    for s in range(len(alp)):
                        loglog(b*m[start:len(m)*fract], (m**(-1-alp[s]))[start:len(m)*fract], label=r"$P_\alpha = %1.2f$" %(alp[s]))
                loglog(x, m)
                hold("on")
                #loglog(x[len(m)*0.5:], m[len(m)*0.5:])
                #hold("on")
            art = []
            lgd = legend(bbox_to_anchor=(0.0, 1.06, 1., 0.102), loc=3, ncol=2, mode="expand", borderaxespad=0.0)
            title(r"$N = %g, \lambda = %g$" %(N[k], Lambda[i]), fontsize = 16) 
            xlabel(r"$m$", fontsize = 16)
            ylabel("Probability Distribution", fontsize = 16)
            tick_params(labelsize=14)
            fig.set_tight_layout(True)
            savefig("plots/d_Pareto_"+str(k+1)+".png", additional_artists=art, bbox_inches="tight")
    show()
    return "Done."

Pareto()

