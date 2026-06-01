import numpy
import scipy

detnum = [97, 101, 102.5, 105, 108.5, 123, 127.5, 129.5, 133.5, 136, 136.5, 140]

large = True

efficiency1 = [13, 13, 15.5, 20]
efficiency2 = [15, 15, 16, 17]
efficiency = []

det = 0

if det == 105 or det == 102.5 or det == 108.5 or det == 123 or det == 129.5 or det == 136 or det == 140:
  large = True
else:
  large = False

states = [2.345, 2.751, 4.8, 6.985]

if large == True:
  solidangle = 0.0020
  efficiency.extend(efficiency1)
else:
  solidangle = 0.0005
  efficiency.extend(efficiency2)

factor = 0

for i in range(len(detnum)):
  for j in range(len(states)):
    det = detnum[i]
    if det == 105 or det == 102.5 or det == 108.5 or det == 123 or det == 129.5 or det == 136 or det == 140:
      large = True
    else:
      large = False
    if large == True:
      solidangle = 0.0020
      efficiency.extend(efficiency1)
    else:
      solidangle = 0.0005
      efficiency.extend(efficiency2)
    factor = ( 0.01 * efficiency[j] ) * solidangle
    print(f"Angle: {det}, State: {states[j]} large: {large}, Factor: {factor}")
