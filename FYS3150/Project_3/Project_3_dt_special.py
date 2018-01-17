from itertools import *
from os import *
from pylab import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D

"""
README: https://github.com/wiggoen/FYS3150/blob/master/Project_3/README.md
"""

# Loading data
SE_E1 = loadtxt("outputs/SE_E_N10000_dt1e-1.txt") 
SE_V1 = loadtxt("outputs/SE_V_N10000_dt1e-1.txt") 
SE_E2 = loadtxt("outputs/SE_E_N10000_dt1e-2.txt") 
SE_V2 = loadtxt("outputs/SE_V_N10000_dt1e-2.txt") 
SE_E3 = loadtxt("outputs/SE_E_N10000_dt1e-3.txt") 
SE_V3 = loadtxt("outputs/SE_V_N10000_dt1e-3.txt") 
SE_E4 = loadtxt("outputs/SE_E_N10000_dt1e-4.txt") 
SE_V4 = loadtxt("outputs/SE_V_N10000_dt1e-4.txt") 


# Sun-Earth with dt = 0.1 and dt = 0.01
def Sun_Earth_1():
    fig = figure()
    
    subplot(2,2,1)
    plot(0, 0, "or", SE_E1[1::2][:, 0], SE_E1[1::2][:, 1], "-b")
    title("dt = 0.1")
    ylabel("y direction [AU]", fontsize = 16) 
    axis("equal")
    
    subplot(2,2,2)
    title("dt = 0.1")
    plot(0, 0, "or", SE_V1[1::2][:, 0], SE_V1[1::2][:, 1], "-g")
    ylabel("y direction [AU]", fontsize = 16) 
    axis("equal")
    
    subplot(2,2,3)
    title("dt = 0.01")
    plot(0, 0, "or", SE_E2[1::2][:, 0], SE_E2[1::2][:, 1], "-b")
    xlabel("x direction [AU]", fontsize = 16)
    ylabel("y direction [AU]", fontsize = 16) 
    axis("equal")

    subplot(2,2,4)
    title("dt = 0.01")
    plot(0, 0, "or", SE_V2[1::2][:, 0], SE_V2[1::2][:, 1], "-g")
    xlabel("x direction [AU]", fontsize = 16)
    ylabel("y direction [AU]", fontsize = 16)  
    axis("equal") 

    fig.set_tight_layout(True)
    savefig("plots/SE1_diff_dt.png")
    show()
    return "The system has been plotted."

print Sun_Earth_1()

# Sun-Earth with dt = 0.001 and dt = 0.0001
def Sun_Earth_2():
    fig = figure()
    
    subplot(2,2,1)
    plot(0, 0, "or", SE_E3[1::2][:, 0], SE_E3[1::2][:, 1], "-b")
    title("dt = 0.001")
    ylabel("y direction [AU]", fontsize = 16) 
    axis("equal")
    
    subplot(2,2,2)
    title("dt = 0.001")
    plot(0, 0, "or", SE_V3[1::2][:, 0], SE_V3[1::2][:, 1], "-g")
    ylabel("y direction [AU]", fontsize = 16) 
    axis("equal")
    
    subplot(2,2,3)
    title("dt = 0.0001")
    plot(0, 0, "or", SE_E4[1::2][:, 0], SE_E4[1::2][:, 1], "-b")
    xlabel("x direction [AU]", fontsize = 16)
    ylabel("y direction [AU]", fontsize = 16) 
    axis("equal")

    subplot(2,2,4)
    title("dt = 0.0001")
    plot(0, 0, "or", SE_V4[1::2][:, 0], SE_V4[1::2][:, 1], "-g")
    xlabel("x direction [AU]", fontsize = 16)
    ylabel("y direction [AU]", fontsize = 16)  
    axis("equal") 

    fig.set_tight_layout(True)
    savefig("plots/SE2_diff_dt.png")
    show()
    return "The system has been plotted."

print Sun_Earth_2()
