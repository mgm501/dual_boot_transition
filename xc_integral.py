import scipy
from scipy.integrate import quad
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as matplotlib
matplotlib.use('TkAgg')
from numpy import pi, sin

coulomb = 6.24e18
proj_q = 2 * (1/coulomb)
target_q = 3 * (1/coulomb)
mev2joule = 1.602e-13
proj_energy = 7 * mev2joule
vacuum_perm = 8.85e-12
meter2barn = 10e28
ringnum = 16

scalingconst = ((proj_q * target_q)/(16*pi*proj_energy*vacuum_perm))**2

def rutherford_xc(x):
  return scalingconst * (1/sin(x/2))**4

def sigma(x):
  return 2 * pi * rutherford_xc(x) * sin(x)

x_data = np.linspace(0.1,pi,1000)
data = rutherford_xc(x_data)
plt.plot(x_data,data)
plt.xlabel('Angle (CM in radians)')
plt.ylabel('Cross Section (meter^2/steradian)')

integral = 0
s1int = 0
s2int = 0

#================================================================================================
ang1 = 6
ang2 = 7
#================================================================================================

#results = []
s2 = []
s1 = []
init_s2angle = 16.1
init_s1angle = 21.16
#for i in range(len(x_data)):
result, err = quad(sigma, (ang1*pi/180) , (ang2*pi/180))
s2compresult, s2cerr = quad(sigma, (14.32*pi/180), (36.67*pi/180))
s1compresult, s1cerr = quad(sigma, (13.9*pi/180), (26.33*pi/180))
#integral += result
#s1int += s1compresult
#s2int += s2compresult

counter1 = 0
counter2 = 0

while init_s2angle < 40.1:
  results2, errs2 = quad(sigma, (init_s2angle*pi/180), ((init_s2angle + 1.5)*pi/180))
  s2.append(results2)
  init_s2angle += 1.5
  counter1 += 1
#print(counter1)
while init_s1angle < 37.75:
  results1, errs1 = quad(sigma, (init_s1angle*pi/180), ((init_s2angle + 1.04)*pi/180))
  s1.append(results1)
  init_s1angle += 1.04
  counter2 += 1
#print(counter2)

#print(f"Integral from {ang1} to {ang2} deg: {integral:.3e}\nScaling Constant: {scalingconst:.3e}")

pps = 6.24e10
#rho = (0.2 * 6.022e20)/(7.02 * 1e-4)
rho = 1.74e19 / 1e-4
print(rho)

particle_flux = result * pps * rho
s2p = s2compresult * pps * rho
s1p = s1compresult * pps * rho

s1pps = []
s2pps = []
for i in range(ringnum):
  s1pps.append(s1[i] * pps * rho)
  s2pps.append(s2[i] * pps * rho)

for i in range(ringnum):
  print(f"PPS in ring {i} for S1: {s1pps[i]:.3e} S2: {s2pps[i]:.3e}\n")

print(f"Total pps from {ang1} to {ang2} deg: {particle_flux:.3e}")

#print(f"Comparison with previous S2: {s2p:.3e}   S1: {s1p:.3e}")

#plt.show()
