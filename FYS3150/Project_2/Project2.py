from matplotlib.pyplot import *
from numpy import *

def single_electron(source, rho_max, num):
    eigvec = loadtxt(source)
    r = linspace(0, rho_max, len(eigvec[:, 0]))
    figure(num)
    plot(r, eigvec[:, 0]**2, r, eigvec[:, 1]**2, r, eigvec[:, 2]**2)
    xlabel(r'$\rho$', fontsize = 16)
    ylabel(r'$Radial$ $probability$ $|u(\rho)|^2$', fontsize = 16)
    legend([r"$|u_0(\rho)|^2$", r"$|u_1(\rho)|^2$", r"$|u_2(\rho)|^2$"], fontsize = 16)
    title(r'$Radial$ $probability$ $distributions$ $for$ $the$ $HO-potential$', fontsize = 18)
    tick_params(labelsize=14)
    figure(num).set_tight_layout(True)
    savefig('plots/Eigvec_GS_HO.png')
    show()
    return "Plotted the three ground states for HO."

s = "outputs/Eigenvectors-HO.txt"
print single_electron(s, 5, 1) # Three first ground states for HO

def two_electron(source1, source2, rho_max1, omega_r1, num, source3, source4, rho_max2, omega_r2):
    eigvec1 = loadtxt(source1)
    eigvec2 = loadtxt(source2)
    eigvec3 = loadtxt(source3)
    eigvec4 = loadtxt(source4)
    r1 = linspace(0, rho_max1, len(eigvec1[:, 0]))
    r2 = linspace(0, rho_max2, len(eigvec3[:, 0]))
    w1 = str(omega_r1)
    w2 = str(omega_r2)
    figure(num)
    subplot(211)
    plot(r1, eigvec1[:, 0]**2, r1, eigvec2[:, 0]**2)
    title(r'$Ground$ $state$ $of$ $two$ $electrons$ $with$ $\omega_r = %1.2f$' %omega_r1, fontsize = 18)
    xlabel(r'$\rho$', fontsize = 16)
    ylabel(r'$Radial$ $probability$ $|u_0(\rho)|^2$', fontsize = 16)
    legend([r"$CO$", r"$HO_{2e}$"], fontsize = 16)
    tick_params(labelsize=14)
    subplot(212)
    plot(r2, eigvec3[:, 0]**2, r2, eigvec4[:, 0]**2)
    title(r'$Ground$ $state$ $of$ $two$ $electrons$ $with$ $\omega_r = %1.2f$' %omega_r2, fontsize = 18)
    xlabel(r'$\rho$', fontsize = 16)
    ylabel(r'$Radial$ $probability$ $|u_0(\rho)|^2$', fontsize = 16)
    legend([r"$CO$", r"$HO_{2e}$"], fontsize = 16)
    tick_params(labelsize=14)
    figure(num).set_tight_layout(True)
    savefig('plots/CO_HO2e_GS_w'+w1+'_w'+w2+'.png')
    show()
    return "Plotted the eigenvectors for CO and HO_2e."

s1 = "outputs/Eigenvectors-CO-w_0.010000.txt"
s2 = "outputs/Eigenvectors-HO_2e-w_0.010000.txt"
s3 = "outputs/Eigenvectors-CO-w_0.500000.txt"
s4 = "outputs/Eigenvectors-HO_2e-w_0.500000.txt"
s5 = "outputs/Eigenvectors-CO-w_1.000000.txt"
s6 = "outputs/Eigenvectors-HO_2e-w_1.000000.txt"
s7 = "outputs/Eigenvectors-CO-w_5.000000.txt"
s8 = "outputs/Eigenvectors-HO_2e-w_5.000000.txt"

# two_electron(source1, source2, rho_max1, omega_r1, num, source3, source4, rho_max2, omega_r2)
# CO and HO_2e for omega_r = 0.01 og omega_r = 0.5
print two_electron(s1, s2, 50, 0.01, 2, s3, s4, 7, 0.5) 

# CO and HO_2e for omega_r = 1.0 og omega_r = 5.0
print two_electron(s5, s6, 5, 1.0, 2, s7, s8, 2, 5.0) 

