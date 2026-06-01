import numpy
import scipy

m = 1.67e-27
d = 2.

t = float(input("Time Difference (ns): "))
ts = t * 1.e-9
E = (1/2) * m * (d/ts)**2
MeV = E * 6.24e12
print(MeV)

