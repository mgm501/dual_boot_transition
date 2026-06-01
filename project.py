# (07/26/23) Hey so I wanted to challenge myself and write a MC generating program in Python. I think I'll just go with scipy, but I also want to challenge myself and create a random number generator from the ground up. I'm thinking about simulating the decay rate of U-235 and other assorted elements.

# (07/30/2023) Turns out U-235 is super long-lived. So I'm going to scrap it and I'll replace it with other shorter lived isotopes.
# Update 2: Finished it. Calling it basic would be an understatement, but it's a good start. When I have free time, I'll think of some widgets I can add on.

import scipy as sc
import numpy as np
from math import exp
x = str(input("Which element are you interested in? (More elements coming soon!): \n U-235 (Out of Stock!) \n C-10 \n Be-13 \n Element:"));
time = float(input("How many seconds will this isotope be left alone?" ));
N0 = float(input("Number of atoms?" ));
Tc = 19.3;
Tbe = 2.7e-21;
if x == "U-235":
    T = 0
elif x == "C-10":
    T = Tc
elif x == "Be-13":
    T = Tbe
l = 0.693/T;
N = N0 * exp(-l * time);
print(N)
