from pylab import *

variance = loadtxt("outputs/variance.txt")
x = arange(len(variance))
plot(x, variance)
ylabel(r"$\sigma^2 = Var(m)$")
xlabel("Transactions")
savefig("plots/a_variance_m.png")
show()