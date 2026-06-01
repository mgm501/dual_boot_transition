import scipy.misc
from math import cos, sqrt, sin

def f(x): 
    return cos(x) + sin(sqrt(x))*sin(sqrt(x))
x = scipy.misc.derivative(f, 1.0, dx = 1e-8)
print(x)
