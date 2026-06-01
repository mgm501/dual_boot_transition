import numpy
from numpy import cos
from numpy import arange
from numpy import deg2rad
from numpy import rad2deg
from numpy import sqrt
from numpy import exp
from numpy import radians
import csv

# page 382 of Krane for equation

# a + X -> b + Y ==> 3He + 7Li -> n + 9B

'''
oxygen levels = {0} MeV
resulting Q = {-1.15}
boron levels = {0,1.5,2.345,2.751,2.78,4.8,6.985,11.64,14.01} MeV
boron q =     {9.35,-,7.01, 6.6,  6.57,4.55,2.37,-2.29, -4.66} MeV
'''
amutomev = 931.5
hemass = 3.016029 * amutomev #3helium mass MeV/c^2
alphamass = 3727.38 #alpha mass
neonmass = 19552.19 #neon
oxymass2 = 16758 #18oxy mass
neutronmass = 939.565 #neutron mass
neutronsi = 1.674927e-27 #neutron SI mass
protonsi = 1.67e-27
nemass20 = 19.9924 * amutomev
nemass21 = 20.9938 * amutomev
oxymass17 = 16.9991 * amutomev
bormass11 = 11.0093 * amutomev
beamenergy = 7 #beam energy 7 for li 
bormass = 9.01333 * amutomev #9B mass
oxymass = 13050.32 #14O mass
neonmass = 19.99244*931.5 #20Ne mass in MeV/c^2
gsq = 9.35 #q - value with gs boron
fsq = 7.85 #q - value with 1 state boron
ssq = 7.01 #q - value with 2 state boron
tsq = 6.6 #q - value with 3 state boron
o1q = -1.15 #q - value with gs oxy
evtoj = 1.6022e-19

ba = 0.6109
bb = 1.946
bc = 0.2625
sa = 0.6193
sb = 2.036
sc = 0.2592
'''
ba = 0.8666
bb = 11.2839
bc = 0.0609
sa = 0.8666
sb = 11.2839
sc = 0.0609
'''

#flightpath = 2 #flight path 2.083
#flightpath = 1.71

v = input("Residual Element or ToF?: ")

if v == "tof" or v == "ToF" or v == "TOF":

  flightpath = float(input("Flightpath?: "))
 
  nenergy0 = float(input("Expected lower bound (MeV): "))
  nenergy1 = float(input("Expected upper bound (MeV): "))

  if nenergy0 == nenergy1:
    nenergy = nenergy0
    nenergysi = nenergy * 1e6 * evtoj
    t = (flightpath * sqrt(neutronsi/(2*nenergysi))) * 1e9
    print(t)

  else:
    nenergy0si = nenergy0 * 1e6 * evtoj
    nenergy1si = nenergy1 * 1e6 * evtoj
    t0 = flightpath * sqrt(neutronsi/(2*nenergy0si))
    t1 = flightpath * sqrt(neutronsi/(2*nenergy1si))
    t0ns = t0 * 1e9
    t1ns = t1 * 1e9
    print(t0ns, t1ns)
  
  for w in range(0,1,1):
    break

else:

  ener = input("Known or unknown neutron energy?: ")

  csvinput = input("save to csv?")

  if csvinput == "":
    if ener == "known" or ener == "k":
      T_b0 = float(input("Neutron Energy: "))
      flightpath = float(input("Flightpath?: "))
      T_N0 = (flightpath * ( neutronsi / (2*T_b0*1.6022e-13) )**0.5) * 1e9 #ToF for neutron
    
      T_G = flightpath / 3e8 #Gamma ToF
      T_Gnano = T_G * 1e9
      neutrontime = "{:.3e}".format(T_N0)
      gammatime = "{:.3e}".format(T_Gnano)
      gammaneutrontimediff = "{:.3e}".format(T_N0-T_Gnano)
      print(f"ToF: {neutrontime}")
    else:
    
      projectile = input("Projectile?: ")
    
      ejectile = input("Ejectile?: ")
    
      residual = input("Residual?: ")
    
      flightpath = float(input("Flightpath?: "))
  
      #flightpath = 1.93
      #flightpath1 = 2.083
    
      be = float(input("Beam energy? (MeV): "))
    
      '''
      size = input("Size? ")
      
      if size == "big":
        aconst = ba
        bconst = bb
        cconst = bc
      
      if size == "small":
        aconst = sa
        bconst = sb
        cconst = sc
      '''
      if projectile == "11B" or projectile == "11b":
        projmass = bormass11
    
      elif projectile == "He" or projectile == "3He" or projectile == "3he":
        projmass = hemass
    
      if ejectile == "n" or ejectile == "N" or ejectile == "neutron":
        ejmass = neutronmass
    
      #if ejectile == "2n":
        #ejmass = 2 * neutronmass
        #neutronsi = 2 * neutronsi
        
      if residual == "O" or residual == "14O" or residual == "14o":
        www = float(input("Residual Nucleon number?: "))
        if www == 14:
          residualmass = oxymass
      
          print("Only populates gs")
          Q0 = o1q
          Q1 = o1q
        elif www == 17:
          residualmass = oxymass17
          Q0 = 6.91
          Q1 = 6.04
      
      if residual == "Ne" or residual == "ne":
        www = float(input("Nucleon number?: "))
        if www == 20:
          residualmass = nemass20
          Q0 = 8.23
          Q1 = 6.6
        if www == 21:
          residualmass = nemass21
          Q0 = 15
          Q1 = 14.65
    
      if residual == "9B" or residual == "9b":
        residualmass = bormass
        Q0 = 9.35 #gs
        Q1 = 7.01  #2.345
        Q2 = 6.6  #did not include Q value for 2.78 MeV (6.57) due to close proximity with 2.751 MeV state. This is 2.751
        Q3 = 4.55 #4.8
        Q4 = 2.37 #6.985
        Q5 = -2.29  #11.64
        Q6 = -2.81  #12.16 MeV
        # yy = input("Output?: ")
    
      d = [1.97, 0, 1.935, 1.99, 1.99, 2.02, 2.03, 2.08, 2.09, 0, 1.94, 1.98, 0.85, 1.98, 2.08, 0.86, 1.94]
      Angle = [127.5, 0, 136.5, 101, 133.5, 111.5, 105, 97, 108.5, 0, 140, 123, 44, 136, 102.5, 54, 129.5]
      l = []
      T = []
      TN = []
      csvfile = "carbontof.csv"
  
      energysi = (2.32) * 1.6e-13
      
      beamtof = 3.99 * sqrt( (5.01e-27) / (2.*energysi) )
      
      beamtofn = beamtof * 1e9
      
      print("Angle, gamma,   first,   gs,      first-gs, gamma-gs, gs ne,  1st ne")
      
      for i in arange(0,181,1):
        '''
        if i == 127.0:
          a = .107
          b = -20.
      
        elif i == 45.:
          a = 0.82
          b = -59.6
      
        elif i == 137.0:
          a = 0.163
          b = -73.9
      
        elif i == 100.:
          a = .0966
          b = -57.6
      
        elif i == 132.0:
          a = 0.0984
          b = -18.
      
        elif i == 110.:
          a = .108
          b = -25.3
      
        elif i == 105.0:
          a = 0.112
          b = -37.5
      
        elif i == 97.5:
          a = .0791
          b = -13.5
      
        elif i == 107.5:
          a = 0.098
          b = -79.7
      
        elif i == 112.5:
          a = .05
          b = 30.5
      
        elif i == 139.5:
          a = 0.0938
          b = -70.9
      
        elif i == 124.5:
          a = 0.0973
          b = -10.9
      
        elif i == 47.5:
          a = 0.0743
          b = -14.
          #flightpath = 1.
      
        elif i == 134.5:
          a = 0.0967
          b = -37.3
      
        elif i == 102.5:
          a = 0.0856
          b = -40.6
      
        elif i == 50.:
          a = .126
          b = -68.3
          #flightpath = 1.
      
        elif i == 129.5:
          a = .0889
          b = -28.9
      
        else:
          a = 1.
          b = 0.
      
        if i == 47.5 or i == 50. or i == 45.:
          flightpath = 1.
      
        else:
          flightpath = 2.083
        '''
    
        m = deg2rad(i)
      
        j = ( (projmass * ejmass * be) ** 0.5 )*cos(m)
        
        k = (projmass * ejmass * be * ((cos(m)) ** 2) )
      
        masst = residualmass + ejmass
    
        if residual == "9B" or residual == "9b":
          
          l0 = (masst) * ( (residualmass * Q0) + ( (residualmass - projmass) * be) )
          l1 = (masst) * ( (residualmass * Q1) + ( (residualmass - projmass) * be) )
          l2 = (masst) * ( (residualmass * Q2) + ( (residualmass - projmass) * be) )
          l3 = (masst) * ( (residualmass * Q3) + ( (residualmass - projmass) * be) )
          l4 = (masst) * ( (residualmass * Q4) + ( (residualmass - projmass) * be) )
          l5 = (masst) * ( (residualmass * Q5) + ( (residualmass - projmass) * be) )
          l6 = (masst) * ( (residualmass * Q6) + ( (residualmass - projmass) * be) )
        
          T_b0 = ( (j + (k + l0) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
          T_b1 = ( (j + (k + l1) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
          T_b2 = ( (j + (k + l2) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
          T_b3 = ( (j + (k + l3) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
          T_b4 = ( (j + (k + l4) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
          T_b5 = ( (j + (k + l5) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
          T_b6 = ( (j + (k + l6) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
    
          T_N0 = "{:.3e}".format((flightpath * ( neutronsi / (2 * T_b0 * 1.6022e-13) ) ** 0.5) * 1e9 )#ToF for neutron
          T_N1 = "{:.3e}".format((flightpath * ( neutronsi / (2 * T_b1 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N2 = "{:.3e}".format((flightpath * ( neutronsi / (2 * T_b2 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N3 = "{:.3e}".format((flightpath * ( neutronsi / (2 * T_b3 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N4 = "{:.3e}".format((flightpath * ( neutronsi / (2 * T_b4 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N5 = "{:.3e}".format((flightpath * ( neutronsi / (2 * T_b5 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N6 = "{:.3e}".format((flightpath * ( neutronsi / (2 * T_b6 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          
          #with open(csvfile, 'w', newline='') as file:
          #writer = csv.writer(file)
        
          '''
          for i in range(0,17):
              j1 = ( (projmass * ejmass * be) ** 0.5 )*cos(Angle[i])
              k1 = (projmass * ejmass * be * ((cos(Angle[i])) ** 2) )
              l0 = (masst) * ( (residualmass * Q0) + ( (residualmass - projmass) * be) )
              l1 = (masst) * ( (residualmass * Q1) + ( (residualmass - projmass) * be) )
              l2 = (masst) * ( (residualmass * Q2) + ( (residualmass - projmass) * be) )
              l3 = (masst) * ( (residualmass * Q3) + ( (residualmass - projmass) * be) )
              l4 = (masst) * ( (residualmass * Q4) + ( (residualmass - projmass) * be) )
              l5 = (masst) * ( (residualmass * Q5) + ( (residualmass - projmass) * be) )
              l6 = (masst) * ( (residualmass * Q6) + ( (residualmass - projmass) * be) )
              
              T_b0 = ( (j1 + (k1 + l0) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
              T_b1 = ( (j1 + (k1 + l1) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
              T_b2 = ( (j1 + (k1 + l2) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
              T_b3 = ( (j1 + (k1 + l3) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
              T_b4 = ( (j1 + (k1 + l4) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
              T_b5 = ( (j1 + (k1 + l5) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
              T_b6 = ( (j1 + (k1 + l6) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
        
              T_N0 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b0 * 1.6022e-13) ) ** 0.5) * 1e9 )#ToF for neutron
              T_N1 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b1 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
              T_N2 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b2 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
              T_N3 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b3 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
              T_N4 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b4 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
              T_N5 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b5 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
              T_N6 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b6 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
              data = [[Angle[i]], [T_N0], [T_N1], [T_N2], [T_N3], [T_N4], [T_N5], [T_N6]]
              print(f"Angle: {Angle[i]} \n Times of Flight: \n Ground State: {T_N0} \n Second State (2.345): {T_N1} \n Third State (2.751): {T_N2} \n Fifth State (4.8): {T_N3} \n Sixth State (6.985): {T_N4} \n Seventh State (11.64): {T_N5} \n Eight State (12.16) : {T_N6}")
              for row in data:
                writer.writerow(row)
                '''
          T_G = flightpath / 3e8 #Gamma ToF
        
          T_Gnano = T_G * 1e9
          #w0 = "{:.3e}".format(T_N0)
          angle = "{:.3e}".format(i)
          #w1 = "{:.3e}".format(T_N1)
          #w3 = "{:.3e}".format(T_N1)
          #w1 = "{:.3e}".format(T_b0)
          #w2 = "{:.3e}".format(T_b1)
          #yupp = "{:.3e}".format(T_N1-T_N0)
          #yuppp = "{:.3e}".format(T_N0-T_Gnano)
          print(f"Angle: {angle} \n Times of Flight: \n Ground State: {T_N0} \n Second State (2.345): {T_N1} \n Third State (2.751): {T_N2} \n Fifth State (4.8): {T_N3} \n Sixth State (6.985): {T_N4} \n Seventh State (11.64): {T_N5} \n Eight State (12.16) : {T_N6}")
  
      else:
          for i in range(0,180):
            j = ( (projmass * ejmass * be) ** 0.5 )*cos(deg2rad(i))
            k = (projmass * ejmass * be * ((cos(deg2rad(i))) ** 2) )
            masst = residualmass + ejmass
            l0 = (masst) * ( (residualmass * Q0) + ( (residualmass - projmass) * be) )
            l1 = (masst) * ( (residualmass * Q1) + ( (residualmass - projmass) * be) )
          
            T_b0 = ( (j + (k + l0) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
            T_b1 = ( (j + (k + l1) ** 0.5 ) / (masst) )**2 #neutron energy in MeV
      
            T_N0 = "{:.3e}".format((flightpath * ( neutronsi / (2 * T_b0 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
            T_N1 = "{:.3e}".format((flightpath * ( neutronsi / (2 * T_b1 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
    
            T_G = flightpath / 3e8 #Gamma ToF
          
            T_Gnano = T_G * 1e9
            #w0 = "{:.3e}".format(T_N0)
            angle = "{:.3e}".format(i)
            #w1 = "{:.3e}".format(T_N1)
            #w3 = "{:.3e}".format(T_N1)
            #w1 = "{:.3e}".format(T_b0)
            #w2 = "{:.3e}".format(T_b1)
            #yupp = "{:.3e}".format(T_N1-T_N0)
            #yuppp = "{:.3e}".format(T_N0-T_Gnano)
            print(f"Angle: {angle} \n Times of Flight: \n Ground State: {T_N0} \n Neutron Energy (MeV): {T_b0}")
      #print(f"Residual Mass: {residualmass}  Projectile Mass: {projmass}  Ejectile Mass: {ejmass}")

  elif csvinput == "yes" or csvinput == "y":
    ask = input("Residual Nucleus? ")
    if ask == "lithium" or ask == "li":
      csvfile = "correctedtof.csv"
      residualmass = bormass
      Q0 = 9.35 #gs0
      Q1 = 7.01  #2.345
      Q2 = 6.6  #did not include Q value for 2.78 MeV (6.57) due to close proximity with 2.751 MeV state. This is 2.751
      Q3 = 4.55 #4.8
      Q4 = 2.37 #6.985
      Q5 = -2.29  #11.64
      Q6 = -2.81  #12.16 MeV
      projmass = hemass
      ejmass = neutronmass
      be = 7.
      masst = residualmass + ejmass
      #print(f"Residual Mass: {masst} Projectile Mass: {projmass} Ejectile Mass: {ejmass}")
      d =     [0.85, 0.86, 2.08, 1.99, 2.08, 2.03, 2.09, 2.02, 1.98, 1.97, 1.94, 1.99, 1.98, 1.935, 1.94, 0, 0]
      Angle = deg2rad([44, 54, 97, 101, 102.5, 105, 108.5, 111.5, 123, 127.5, 129.5, 133.5, 136, 136.5, 140, 0, 0])
      with open(csvfile, 'w', newline='') as file:
        writer = csv.writer(file)
        for i in range(0,17):
          j1 = ( (projmass * ejmass * be) ** 0.5 )*cos(Angle[i])
          k1 = (projmass * ejmass * be * ((cos(Angle[i]))**2) )
          l0 = (masst) * ( (residualmass * Q0) + ( (residualmass - projmass) * be) )
          l1 = (masst) * ( (residualmass * Q1) + ( (residualmass - projmass) * be) )
          l2 = (masst) * ( (residualmass * Q2) + ( (residualmass - projmass) * be) )
          l3 = (masst) * ( (residualmass * Q3) + ( (residualmass - projmass) * be) )
          l4 = (masst) * ( (residualmass * Q4) + ( (residualmass - projmass) * be) )
          l5 = (masst) * ( (residualmass * Q5) + ( (residualmass - projmass) * be) )
          l6 = (masst) * ( (residualmass * Q6) + ( (residualmass - projmass) * be) )
          
          T_b0 = ( (j1 + ((k1 + l0)**0.5) ) / (masst) )**2 #neutron energy in MeV
          T_b1 = ( (j1 + ((k1 + l1)**0.5) ) / (masst) )**2 #neutron energy in MeV
          T_b2 = ( (j1 + ((k1 + l2)**0.5) ) / (masst) )**2 #neutron energy in MeV
          T_b3 = ( (j1 + ((k1 + l3)**0.5) ) / (masst) )**2 #neutron energy in MeV
          T_b4 = ( (j1 + ((k1 + l4)**0.5) ) / (masst) )**2 #neutron energy in MeV
          T_b5 = ( (j1 + ((k1 + l5)**0.5) ) / (masst) )**2 #neutron energy in MeV
          T_b6 = ( (j1 + ((k1 + l6)**0.5) ) / (masst) )**2 #neutron energy in MeV
    
          T_N0 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b0 * 1.6022e-13) ) ** 0.5) * 1e9 )#ToF for neutron
          T_N1 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b1 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N2 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b2 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N3 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b3 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N4 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b4 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N5 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b5 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          T_N6 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b6 * 1.6022e-13) ) ** 0.5) * 1e9 ) #ToF for neutron
          data = [['Angle', 'ToF', 'Energies'], [Angle[i], T_N0, T_b0], [Angle[i], T_N1, T_b1], [Angle[i], T_N2, T_b2], [Angle[i], T_N3, T_b3], [Angle[i], T_N4, T_b4], [Angle[i],T_N5, T_b5], [Angle[i],T_N6, T_b6]]
          print(f"Angle: {rad2deg(Angle[i])} \n Times of Flight: \n Ground State: {T_b0} \n Second State (2.345): {T_b1} \n Third State (2.751): {T_b2} \n Fifth State (4.8): {T_b3} \n Sixth State (6.985): {T_N4} \n Seventh State (11.64): {T_N5} \n Eight State (12.16) : {T_N6}")
          for row in data:
            writer.writerow(row)

    elif ask == "oxy" or ask == "o" or ask == "oxygen":
      csvfile = "carbontof.csv"
      residualmass = oxymass
      Q0 = o1q #gs0
      projmass = hemass
      ejmass = neutronmass
      be = 7.
      masst = residualmass + ejmass
      #print(f"Residual Mass: {masst} Projectile Mass: {projmass} Ejectile Mass: {ejmass}")
      d =     [0.85, 0.86, 2.08, 1.99, 2.08, 2.03, 2.09, 2.02, 1.98, 1.97, 1.94, 1.99, 1.98, 1.935, 1.94, 0, 0]
      Angle = deg2rad([44, 54, 97, 101, 102.5, 105, 108.5, 111.5, 123, 127.5, 129.5, 133.5, 136, 136.5, 140, 0, 0])
      with open(csvfile, 'w', newline='') as file:
        writer = csv.writer(file)
        for i in range(0,17):
          j1 = ( (projmass * ejmass * be) ** 0.5 )*cos(Angle[i])
          k1 = (projmass * ejmass * be * ((cos(Angle[i]))**2) )
          l0 = (masst) * ( (residualmass * Q0) + ( (residualmass - projmass) * be) )
          
          T_b0 = ( (j1 + ((k1 + l0)**0.5) ) / (masst) )**2 #neutron energy in MeV
    
          T_N0 = "{:.3e}".format((d[i] * ( neutronsi / (2 * T_b0 * 1.6022e-13) ) ** 0.5) * 1e9 )#ToF for neutron
          data = [['Angle', 'ToF', 'Energies'], [Angle[i], T_N0, T_b0]]
          print(f"Angle: {rad2deg(Angle[i])} \n Times of Flight: \n Ground State: {T_b0}")
          for row in data:
            writer.writerow(row)
            