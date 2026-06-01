import numpy as np
import sympy as sp
from scipy.optimize import curve_fit
import scipy as sc
from scipy.stats import chi2
import pandas as pd
import matplotlib.pyplot as plt
import math

def fit_function(x, a, b, c, d):
  return -a*(np.log(b*x + c))**2 + d

path2x2 = '2x2test.csv'
path4x2 = 'Dataset4x2.csv'

df2x2 = pd.read_csv(path2x2)
df4x2 = pd.read_csv(path4x2)

cola2x2 = df2x2['Column1']
colb2x2 = df2x2['Column2']

cola4x2 = df4x2['Column1']
colb4x2 = df4x2['Column2']

cola2x2.dropna(), colb2x2.dropna(), cola4x2.dropna(), colb4x2.dropna()

xdata2x2 = cola2x2.to_numpy()
ydata2x2 = colb2x2.to_numpy()

xdata4x2 = cola4x2.to_numpy()
ydata4x2 = colb4x2.to_numpy()

#xdata = np.concatenate((xdata,np.array([11,11.5,12,12.5,13,13.5,14,14.5,15,15.5,16])))

#print(ydata)

initial_guess2x2 = [3,0.9,-1,26]
initial_guess4x2 = [2.3,0.7,-1,21]
params2x2, cov2x2 = curve_fit(fit_function, xdata2x2, ydata2x2, p0=initial_guess2x2)
params4x2, conv4x2 = curve_fit(fit_function, xdata4x2, ydata4x2, p0=initial_guess4x2)

a0, b0, c0, d0 = params2x2
a1, b1, c1, d1 = params4x2

print(f"2x2 A: {a0} B: {b0} C: {c0} D: {d0}\n")
print(f"4x2 A: {a1} B: {b1} C: {c1} D: {d1}\n")

fit4x2 = fit_function(cola4x2, a1, b1, c1, d1)
fit2x2 = fit_function(cola2x2, a0, b0, c0, d0)

sigma4x2 = 0.1 * ydata4x2
sigma2x2 = 0.1 * ydata2x2
#print(sigma4x2)

residual4x2 = ydata4x2 - fit4x2
chi2_val4x2 = np.sum( (residual4x2 / sigma4x2)**2 )
dof4x2 = len(ydata4x2) - 5
p_value4x2 = 1 - chi2.cdf(chi2_val4x2,dof4x2)

residual2x2 = ydata2x2 - fit2x2
chi2_val2x2 = np.sum( (residual2x2 / sigma2x2)**2 )
dof2x2 = len(ydata2x2) - 5
p_value2x2 = 1 - chi2.cdf(chi2_val2x2,dof2x2)

#print(f"4x2 chi_square: {chi2_val4x2} 4x2 P-value: {p_value4x2}")
print(f"2x2 chi_square: {chi2_val2x2} 2x2 P-value: {p_value2x2}")

#plt.scatter(cola4x2,colb4x2,label='4x2')
plt.scatter(cola2x2,colb2x2,label='2x2')
#plt.plot(cola4x2,fit4x2,label='4x2fit')
plt.plot(cola2x2,fit2x2,label='2x2fit')

plt.title('4x2 and 2x2')
plt.legend()
plt.show()
