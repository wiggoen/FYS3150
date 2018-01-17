from pylab import *

m1 = loadtxt("outputs/noEqualityForFatCats_run_20k.txt")
m2 = loadtxt("outputs/noEqualityForFatCats_run_1e5.txt")

"""
figure(1)
title("20 000 Transactions")
hist(m1, bins=50)
xlabel(r"$m$", fontsize=16)
ylabel("Agents", fontsize=16)
tick_params(labelsize=14)

figure(2)
title(r"$10^5$ Transactions")
hist(m2, bins=50)
xlabel(r"$m$", fontsize=16)
ylabel("Agents", fontsize=16)
tick_params(labelsize=14)
"""

figure(3)
difference = abs(m2-m1)
plot(difference)
xlabel(r"$m$", fontsize=16)
ylabel(r"Difference between $10^5$ and $20 000$ Transactions", fontsize=16)
tick_params(labelsize=14)
savefig("plots/difference.png")
show()

