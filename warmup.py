# Compute the first derivative of f(x) = arctan(x)

from numpy import *
from matplotlib.pyplot import * 

x = sqrt(2)
h = logspace(-10, -1, 10)

def f(x):
    return arctan(x)

def O(h):
    return -(sqrt(2)/9.)*h

def O2(h):
    return (10./126)*h**2

f_comp2 = (f(x+h)-f(x))/h + O(h)
f_comp3 = (f(x+h)-f(x-h))/(2*h) + O2(h)

dfdx_exact = 1/3.

rel_error2 = abs((f_comp2 - dfdx_exact)/dfdx_exact)
rel_error3 = abs((f_comp3 - dfdx_exact)/dfdx_exact)

#print dfdx_exact
#print rel_error2, rel_error3

#plot(log10(h), log10(rel_error2), log10(h), log10(rel_error3))
loglog(h, rel_error2, h, rel_error3)
title('Error estimation of arctan(x)')
legend(['error2c', 'error3c'])
xlabel('log(h)')
ylabel('error')
show()
