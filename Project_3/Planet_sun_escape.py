from pylab import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D

v_escape = loadtxt("outputs/v_escape.xyz")

fig = figure()
plot(0, 0, "or", v_escape[1::2][:, 0], v_escape[1::2][:, 1], "-b")
title(r"$Planet$ $escape$ $from$ $the$ $sun$, $v_{escape} = 8.9$ AU/yr", fontsize = 18)
xlabel("\n" + r"$x$ $direction$ $[AU]$", fontsize = 16)
ylabel(r"$y$ $direction$ $[AU]$", fontsize = 16)
art = []
lgd = legend([r"$Sun$", r"$Planet$ $orbit$"],loc="upper left", bbox_to_anchor=(1, 1))
art.append(lgd)
tick_params(labelsize=14)
savefig("plots/Planet_sun_escape.png", additional_artists=art, bbox_inches="tight")
show()

