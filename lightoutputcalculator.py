import numpy as np

i = input("Energy Range: ")
if i == "":
  exit()

#input = i.split()

#range0num = float(input[0])

#if input[1] == "":
#  continue
#else:
#range1num = float(input[1])

range0, range1 = i.split()

range0num = float(range0)
range1num = float(range1)

#if input[2] == "":
#  continue

asmall = .6193 
bsmall = 2.036
csmall = .2592
alarge = .6109
blarge = 1.946
clarge = .2625

det = input("Size? ")
if det == "":
  det = "large"
  print("Going with 4x2 (large). To change size, just type 'small' when prompted")
  
if det == "big" or det == "large":
  a, b, c = alarge, blarge, clarge
  #print(f"{a} {b} {c}")
if det == "small" or det == "little":
  a, b, c = asmall, bsmall, csmall

for energy in np.arange(range0num, range1num):
  L = 1000 * (a * ( (8/9) * energy) - b * (1 - np.exp(-c*(8/9)*energy) ) )
  print(f"Max Deposited Energy: {energy:.4f} MeV   Light Output: {L:.4f} keVee \n")
