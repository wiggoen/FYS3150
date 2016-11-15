from pylab import *

source_random = loadtxt("outputs/L20_mcc_random.txt")
source_ordered = loadtxt("outputs/L20_mcc_ordered.txt")

MCC = int(1e6)                   # Monte Carlo Cycles

cycles = source_random[:,1]      # Monte Carlo Cycles

meanE_r = source_random[:,5]     # Current mean energy per cycle per spin
meanM_r = source_random[:,6]     # Current mean magnetization per cycle per spin

meanE_o = source_ordered[:,5]    # Current mean energy per cycle per spin
meanM_o = source_ordered[:,6]    # Current mean magnetization per cycle per spin

aC_r = source_random[:,7]        # Accepted configurations
aC_o = source_ordered[:,7]       # Accepted configurations


stop = int(1e5)                  # Plot for 100k
stop2 = int(5e4)                 # Plot for 50k

# Random spins
fig = figure(1)
subplot(211)

plot(cycles[:MCC-1], meanE_r[:MCC-1])                    # Energy for T = 1.0
hold("on")
plot(cycles[MCC:], meanE_r[MCC:])                        # Energy for T = 2.4
axis([-10000, MCC, -2.1, -0.5])                          # xmin, xmax, ymin, ymax

"""
plot(cycles[:stop], meanE_r[:stop])                      # Energy for T = 1.0
hold("on")
plot(cycles[MCC:(MCC+stop)], meanE_r[MCC:(MCC+stop)])    # Energy for T = 2.4
axis([-1000, stop, -2.1, -0.5])                          # xmin, xmax, ymin, ymax
"""
"""
plot(cycles[:stop2], meanE_r[:stop2])                    # Energy for T = 1.0
hold("on")
plot(cycles[MCC:(MCC+stop2)], meanE_r[MCC:(MCC+stop2)])  # Energy for T = 2.4
axis([-250, stop2, -2.1, -0.5])                          # xmin, xmax, ymin, ymax
"""
art = []
lgd = legend([r"$T$ = 1.0", r"$T$ = 2.4"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel(r"$\langle E/L^2 \rangle$", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

subplot(212)

plot(cycles[:MCC-1], abs(meanM_r[:MCC-1]))                   # Magnetization for T = 1.0
hold("on")
plot(cycles[MCC:], abs(meanM_r[MCC:]))                       # Magnetization for T = 2.4
axis([-10000, MCC, -0.1, 1.1])                               # xmin, xmax, ymin, ymax

"""
plot(cycles[:stop], abs(meanM_r[:stop]))                     # Magnetization for T = 1.0
hold("on")
plot(cycles[MCC:(MCC+stop)], abs(meanM_r[MCC:(MCC+stop)]))   # Magnetization for T = 2.4
axis([-1000, stop, -0.1, 1.1])                               # xmin, xmax, ymin, ymax
"""
"""
plot(cycles[:stop2], abs(meanM_r[:stop2]))                   # Magnetization for T = 1.0
hold("on")
plot(cycles[MCC:(MCC+stop2)], abs(meanM_r[MCC:(MCC+stop2)])) # Magnetization for T = 2.4
axis([-250, stop2, -0.1, 1.1])                               # xmin, xmax, ymin, ymax
"""
art = []
lgd = legend([r"$T$ = 1.0", r"$T$ = 2.4"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel(r"$\langle |M|/L^2 \rangle$", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

savefig("plots/MeansVSmccT124ran_NEW.png", additional_artists=art, bbox_inches="tight")
show()


# Ordered spins
fig = figure(2)
subplot(211)

plot(cycles[:MCC-1], meanE_o[:MCC-1])       # Energy for T = 1.0
hold("on")
plot(cycles[MCC:], meanE_o[MCC:])           # Energy for T = 2.4 
axis([-10000, MCC, -2.1, -0.5])       # xmin, xmax, ymin, ymax

"""
plot(cycles[:stop], meanE_o[:stop])                      # Energy for T = 1.0
hold("on")
plot(cycles[MCC:(MCC+stop)], meanE_o[MCC:(MCC+stop)])    # Energy for T = 2.4 
axis([-1000, stop, -2.1, -0.5])                          # xmin, xmax, ymin, ymax
"""
"""
plot(cycles[:stop2], meanE_o[:stop2])                    # Energy for T = 1.0
hold("on")
plot(cycles[MCC:(MCC+stop2)], meanE_o[MCC:(MCC+stop2)])  # Energy for T = 2.4 
axis([-250, stop2, -2.1, -0.5])                          # xmin, xmax, ymin, ymax
"""
art = []
lgd = legend([r"$T$ = 1.0", r"$T$ = 2.4"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel(r"$\langle E/L^2 \rangle$", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

subplot(212)

plot(cycles[:MCC-1], abs(meanM_o[:MCC-1]))                   # Magnetization for T = 1.0
hold("on")
plot(cycles[MCC:], abs(meanM_o[MCC:]))                       # Magnetization for T = 2.4
axis([-10000, MCC, -0.1, 1.1])                               # xmin, xmax, ymin, ymax

"""
plot(cycles[:stop], abs(meanM_o[:stop]))                     # Magnetization for T = 1.0
hold("on")
plot(cycles[MCC:(MCC+stop)], abs(meanM_o[MCC:(MCC+stop)]))   # Magnetization for T = 2.4
axis([-1000, stop, -0.1, 1.1])                               # xmin, xmax, ymin, ymax
"""
"""
plot(cycles[:stop2], abs(meanM_o[:stop2]))                   # Magnetization for T = 1.0
hold("on")
plot(cycles[MCC:(MCC+stop2)], abs(meanM_o[MCC:(MCC+stop2)])) # Magnetization for T = 2.4
axis([-250, stop2, -0.1, 1.1])                               # xmin, xmax, ymin, ymax
"""
art = []
lgd = legend([r"$T$ = 1.0", r"$T$ = 2.4"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel(r"$\langle |M|/L^2 \rangle$", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

savefig("plots/MeansVSmccT124ord_NEW.png", additional_artists=art, bbox_inches="tight")
show()


stop3 = int(1e4)

# Accepted configurations vs Monte Carlo cycles
fig = figure(3)
subplot(211) # T = 1.0
plot(cycles[:stop3], aC_r[:stop3])
hold("on")
plot(cycles[:stop3], aC_o[:stop3])
axis([-100, stop3, 0, 4500]) 
art = []
lgd = legend([r"Random, $T = 1.0$", r"Ordered, $T = 1.0$"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel("Accepted configurations", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

subplot(212) # T = 2.4
plot(cycles[MCC:(MCC+stop3)], aC_r[MCC:(MCC+stop3)]) 
hold("on")
plot(cycles[MCC:(MCC+stop3)], aC_o[MCC:(MCC+stop3)]) 
axis([-100, stop3, 0, 1.2e6]) 
art = []
lgd = legend([r"Random, $T = 2.4$", r"Ordered, $T = 2.4$"], loc="upper left", bbox_to_anchor=(1, 1))
xlabel("Monte Carlo Cycles", fontsize = 16)
ylabel("Accepted configurations", fontsize = 18)    
art.append(lgd)
tick_params(labelsize=14)
fig.set_tight_layout(True)

savefig("plots/AcceptVSmcc_NEW.png", additional_artists=art, bbox_inches="tight")
show()

