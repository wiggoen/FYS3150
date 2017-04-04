
from matplotlib.pyplot import *
from numpy import *


fig = figure(1)

# Gamma
g1 = [468, 316]
g2 = [604, 308, 136, 486, 612, 296, 316]
g3 = [468, 316, 604, 308, 136, 486, 612, 296, 316, 884, 416, 280, 588]

gamma1 = sorted(g1)
gamma2 = sorted(g2)
gamma3 = sorted(g3)

yoffset = 1200
xoffset = 7

for i in range(len(g3)):
    g = gamma3
    x = xoffset+i
    y = yoffset
    plot([x, x], [y, y-g[i]], "r-")
    annotate('', xy=(x, y), xycoords="data", xytext=(x, y-g[i]), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="red"))
    if (i != 0):
        plot([xoffset, x], [y-g[i], y-g[i]], "k-")
for i in range(len(g2)):
    g = gamma2
    x = xoffset+i+len(g3)
    y = yoffset-280
    plot([x, x], [y, y-g[i]], "g-")
    annotate('', xy=(x, y), xycoords="data", xytext=(x, y-g[i]), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="green"))
    if (i != 0):
        plot([xoffset, x], [y-g[i], y-g[i]], "k-")
for i in range(len(g1)):
    g = gamma1
    x = xoffset+i+len(g3)+len(g2)
    y = yoffset-280-136
    plot([x, x], [y, y-g[i]], "b-")
    annotate('', xy=(x, y), xycoords="data", xytext=(x, y-g[i]), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="blue"))
    if (i != 0):
        plot([xoffset, x], [y-g[i], y-g[i]], "k-")

x = xoffset + len(g1+g2+g3)
y3 = yoffset
y2 = y3-280
y1 = y2-136
plot([xoffset-1, x], [y3, y3], "r-") # (3) 
plot([xoffset-1, x], [y2, y2], "g-") # (2) 
plot([xoffset-1, x], [y1, y1], "b-") # (1)

# Mother
x1 = 3
y = yoffset+200
plot([0, x1], [y, y], "m-")

# Beta
x = xoffset-1
plot([x1, x], [y, yoffset], "r-")
annotate('', xy=(x1, y), xycoords="data", xytext=(x, yoffset), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="red"))
plot([x1, x], [y, yoffset-280], "g-")
annotate('', xy=(x1, y), xycoords="data", xytext=(x, yoffset-280), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="green"))
plot([x1, x], [y, yoffset-280-136], "b-")
annotate('', xy=(x1, y), xycoords="data", xytext=(x, yoffset-280-136), 
         textcoords="data", arrowprops=dict(arrowstyle="<-", color="blue"))

# Beta text
text(5, yoffset+100, r'256 keV $\beta$', fontsize=14, color="red")
text(0.1, yoffset-100, r'536 keV $\beta$', fontsize=14, color="green")
text(1, yoffset-350, r'672 keV $\beta$', fontsize=14, color="blue")

# Energy levels
annotate('', xy=(xoffset+len(g1+g2+g3), yoffset), xycoords="data", xytext=(xoffset+len(g1+g2+g3), yoffset-280), 
         textcoords="data", arrowprops=dict(arrowstyle="<->", color="black"))
annotate('', xy=(xoffset+len(g1+g2+g3), yoffset-280), xycoords="data", xytext=(xoffset+len(g1+g2+g3), yoffset-280-136), 
         textcoords="data", arrowprops=dict(arrowstyle="<->", color="black"))
text(26, yoffset-150, '280 keV', fontsize=14, color="black")
text(26, yoffset-365, '136 keV', fontsize=14, color="black")

axis((0, xoffset+len(g1+g2+g3)+1, yoffset-max(g3)-50, yoffset+250))

ylabel("Energy [keV]", fontsize=16)
tick_params(labelsize=14)
ax = gca()
axis("off")
fig.set_tight_layout(True)
savefig("6a.png")
show()
