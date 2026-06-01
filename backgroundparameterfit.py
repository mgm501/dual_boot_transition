import numpy as np
import scipy as sp

total_entries = 1379
beamenergy = 12

def function0(x):
  #16o reaction
  #x = sp.Symbol('x')
  function0 = (x-7.907)*(x-16.78)
  if function0 >= 0:
    return function0
  else:
    return 0

def function1(x):
  #20F
  function1 = (x-6.742)*(x-15.061)
  if function1 >= 0:
    return function1
  else:
    return 0

def function2(x):
  #13C
  function2 = (x-6.206)*(x-14.254)
  if function2 >= 0:
    return function2
  else:
    return 0

def function3(x):
  #18O
  function3 = (x-1.797)*(x-6.887)
  if function3 >= 0:
    return function3
  else:
    return 0

breakpoints0 = [0,5.591,15.476,20]
breakpoints1 = [0, 6.742, 15.061, 20]
breakpoints2 = [0, 6.206, 14.254, 20]
breakpoints3 = [0, 1.445, 6.486, 20]

if beamenergy == 18:
  desiredratio0 = 0.00411
  desiredratio1 = 0.0131
  desiredratio2 = 0.0284
  desiredratio3 = 0.0614

if beamenergy == 15:
  desiredratio0 = 0.000054
  desiredratio1 = 0.00478
  desiredratio2 = 0.00825
  desiredratio3 = 0.0535

if beamenergy == 12:
  desiredratio0 = 0.
  desiredratio1 = 0.000832
  desiredratio2 = 0.000544
  desiredratio3 = 0.0481

if beamenergy == 9:
  desiredratio0 = 0.
  desiredratio1 = 0.
  desiredratio2 = 0.
  desiredratio3 = 0.

total_integral0 = 0
total_integral1 = 0
total_integral2 = 0
total_integral3 = 0

lowbound = 0
upbound = 20
for i in range(len(breakpoints0) - 1):
  low0 = breakpoints0[i]
  upper0 = breakpoints0[i+1]
  low1 = breakpoints1[i]
  upper1 = breakpoints1[i+1]
  low2 = breakpoints2[i]
  upper2 = breakpoints2[i+1]
  low3 = breakpoints3[i]
  upper3 = breakpoints3[i+1]

  if max(lowbound, low0) < min(upbound, upper0):
    integral0, error0 = sp.integrate.quad(function0, max(lowbound, low0), min(upbound, upper0))
    #print(integral0)
    total_integral0 += integral0

  if max(lowbound, low1) < min(upbound, upper1):
    integral1, error1 = sp.integrate.quad(function1, max(lowbound, low1), min(upbound, upper1))
    total_integral1 += integral1 

  if max(lowbound, low2) < min(upbound, upper2):
    integral2, error2 = sp.integrate.quad(function2, max(lowbound, low2), min(upbound, upper2))
    total_integral2 += integral2 

  if max(lowbound, low3) < min(upbound, upper3):
    integral3, error3 = sp.integrate.quad(function3, max(lowbound, low3), min(upbound, upper3))
    total_integral3 += integral3 

#print(f"Integral: {total_integral:.4f}")
ratio0 = total_integral0/total_entries
ratio1 = total_integral1/total_entries
ratio2 = total_integral2/total_entries
ratio3 = total_integral3/total_entries

correction0 = float(desiredratio0)/ratio0
correction1 = float(desiredratio1)/ratio1
correction2 = float(desiredratio2)/ratio2
correction3 = float(desiredratio3)/ratio3

print(f"Correction factor 16O: {correction0:.4f}\nCorrection factor 20F: {correction1:.4f}\nCorrection factor 13C: {correction2:.4f}\nCorrection factor 18O: {correction3:.4f}\n")

