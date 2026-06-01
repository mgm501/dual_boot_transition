import numpy as np
from numpy import arange
import scipy as sp
import matplotlib.pyplot as plt
from pylab import plot,xlabel,ylabel,show,legend,yscale
# assuming lab angle of 130 degrees
# assuming distance of 2.8 meters

xmin = 50
xmax = 80

x_points = arange(xmin,xmax,0.01)
gs = []
first = []
second = []
third = []
fourth = []
total_spectrum = []

def gaus(x, mu, sigma, amp):
  exponent = np.exp(-np.power(x - mu, 2.) / (2 * np.power(sigma, 2.)))
  return amp * exponent

for x in x_points:
  gs.append(gaus(x,62.357,0.1, 10))
  first.append(gaus(x,66.606,2.49, 8))
  second.append(gaus(x,68.893,0.19, 10))
  third.append(gaus(x,70.342,7.82, 8))
  fourth.append(gaus(x,78.447,4.09,18))
  total_spectrum.append(gaus(x,62.357,0.1, 10) + gaus(x,66.606,2.49, 8) + gaus(x,68.893,0.19, 10) + gaus(x,70.342,7.82, 8) + gaus(x,78.447,4.09,18))

plot(x_points,gs,label="gs")
plot(x_points,first,label="first (~1.6 MeV)")
plot(x_points,second,label="second (2.345 MeV)")
plot(x_points,third,label="third (2.78 MeV)")
plot(x_points,fourth,label="fourth (4.8 MeV)")
plot(x_points,total_spectrum,label="total spectrum")
xlabel("ToF (ns)")
ylabel("Counts (arbitrary)")
plt.legend()

show()
