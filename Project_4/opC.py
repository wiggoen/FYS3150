from pylab import *

source_random = loadtxt("outputs/outfile_c_mcc_random.txt")
source_ordered = loadtxt("outputs/outfile_c_mcc_ordered.txt")

MCC = int(1e6)                   # Monte Carlo Cycles

cycles = source_random[:,1]      # Monte Carlo Cycles

meanE_r = source_random[:,5]     # Current mean energy per cycle per spin
meanM_r = source_random[:,6]     # Current mean magnetization per cycle per spin

meanE_o = source_ordered[:,5]    # Current mean energy per cycle per spin
meanM_o = source_ordered[:,6]    # Current mean magnetization per cycle per spin

#aC = source_mcc[:,7]             # Accepted configurations


# Random spins
fig = figure(1)
subplot(211)
plot(cycles[:MCC-1], meanE_r[:MCC-1])       # Energy for T = 1.0
hold("on")
plot(cycles[MCC:], meanE_r[MCC:])           # Energy for T = 2.4
axis([-10000, MCC+10000, -2.1, -0.5])       # xmin, xmax, ymin, ymax
art = []
lgd = legend([r"$T$ = 1.0", r"$T$ = 2.4"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel(r"$\langle E \rangle$", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

subplot(212)
plot(cycles[:MCC-1], abs(meanM_r[:MCC-1]))  # Magnetization for T = 1.0
hold("on")
plot(cycles[MCC:], abs(meanM_r[MCC:]))      # Magnetization for T = 2.4
axis([-10000, MCC+10000, -0.1, 1.1])        # xmin, xmax, ymin, ymax
art = []
lgd = legend([r"$T$ = 1.0", r"$T$ = 2.4"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel(r"$\langle |M| \rangle$", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

savefig("plots/MeansVSmccT124ran.png", additional_artists=art, bbox_inches="tight")
show()


# Ordered spins
fig = figure(2)
subplot(211)
plot(cycles[:MCC-1], meanE_o[:MCC-1])       # Energy for T = 1.0
hold("on")
plot(cycles[MCC:], meanE_o[MCC:])           # Energy for T = 2.4
axis([-10000, MCC+10000, -2.1, -0.5])       # xmin, xmax, ymin, ymax
art = []
lgd = legend([r"$T$ = 1.0", r"$T$ = 2.4"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel(r"$\langle E \rangle$", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

subplot(212)
plot(cycles[:MCC-1], abs(meanM_o[:MCC-1]))  # Magnetization for T = 1.0
hold("on")
plot(cycles[MCC:], abs(meanM_o[MCC:]))      # Magnetization for T = 2.4
axis([-10000, MCC+10000, -0.1, 1.1])        # xmin, xmax, ymin, ymax
art = []
lgd = legend([r"$T$ = 1.0", r"$T$ = 2.4"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel(r"$\langle |M| \rangle$", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

savefig("plots/MeansVSmccT124ord.png", additional_artists=art, bbox_inches="tight")
show()

