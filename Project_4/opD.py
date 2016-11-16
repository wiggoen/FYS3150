from pylab import *

source_random = loadtxt("outputs/L20_mcc_random.txt")
source_average = loadtxt("outputs/L20_avg_random.txt")

MCC = int(1e6)                   # Monte Carlo Cycles
E_r = source_random[:,2]         # Energy
Var_T1 = source_average[0,8]     # Variance, T = 1.0
Var_T24 = source_average[1,8]    # Variance, T = 2.4

start = 10000

fig = figure()
subplot(121)
hist(E_r[start:MCC-1], bins=8, normed=1, facecolor='blue', alpha=0.75, label=r"$\sigma_E^2$ = %f" %Var_T1)
xticks(rotation='vertical')
grid(True)
art = []
lgd = legend(bbox_to_anchor=(0.0, 1.02, 1., 0.102), loc=3, ncol=2, mode="expand", borderaxespad=0.0)
#lgd = legend(loc="upper left", bbox_to_anchor=(1, 1))
xlabel(r"$E$", fontsize = 18)
ylabel(r"Probability, $P(E)$", fontsize = 16)  
tick_params(labelsize=14)
fig.set_tight_layout(True)

subplot(122)
hist(E_r[(MCC+start):], bins=150, normed=1, facecolor='blue', alpha=0.75, label=r"$\sigma_E^2$ = %f" %Var_T24)  
xticks(rotation='vertical')
grid(True)
art = []
lgd = legend(bbox_to_anchor=(0.0, 1.02, 1., 0.102), loc=3, ncol=2, mode="expand", borderaxespad=0.)
xlabel(r"$E$", fontsize = 18)
ylabel(r"Probability, $P(E)$", fontsize = 16)
tick_params(labelsize=14)
fig.set_tight_layout(True)

savefig("plots/Probability.png", additional_artists=art, bbox_inches="tight")
show()