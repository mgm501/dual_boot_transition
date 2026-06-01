from scipy.optimize import fsolve
import sympy as sp
import numpy as np

projmass = 3.016 * 931.5
ejmass = 939.57
residmass = 9.013 * 931.5
#Q = 9.35 #gs
#Q = 7.01 #2.345
Q = 6.57 #2.78
#Q = 4.55 #4.8
#Q = 2.37 #6.985
#Q = -2.29 #11.64
bombenergy = 7
g = np.sqrt(  (projmass * ejmass * bombenergy) / ( (residmass*(residmass + ejmass)*Q  +  residmass*(residmass + ejmass - projmass)*bombenergy) )  )

#x, y = symbols('x y')
#eq1 = tan(x)
#eq2 = sin(y)/(cos(y)+g)
#sol = solve((eq1,eq2), (x,y))

labangle = float(input("Lab Angle in degrees? "))

def func(x):
  return (np.sin(x)/(np.cos(x)+g)) - np.tan(labangle*np.pi/180)

if labangle < 82:
  initialguess = 1
else:
  initialguess = 2
sol = 180*fsolve(func, initialguess)/np.pi
print(f"CoM Angle: {sol}")
