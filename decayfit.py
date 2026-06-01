#from random import random,uniform
import matplotlib.pyplot as plt
import numpy as np
import math
import scipy
from iminuit import Minuit
#from iminuit.cost import Cost
from iminuit.cost import UnbinnedNLL, ExtendedUnbinnedNLL, ExtendedBinnedNLL, LeastSquares
from scipy.stats import truncnorm, truncexpon, norm, expon

#print(scipy.__version__)

xrange = (2,30)
def f( x, N, mean, sigma ):
    # normalized Gaussian
    return N*norm(x, mean, sigma)

### test data
test_data = np.random.normal(10,2,400)
#print(test_data)

### Examples of fits using iminuit.  Note that it has a lot more cool features!
### https://scikit-hep.org/iminuit/tutorials.html
### https://indico.cern.ch/event/833895/contributions/3577808/attachments/1927550/3191336/iminuit_intro.html

## actual data
data = [4.99, 4.87, 2.59, 3.04, 3.39, 6.20, 10.61, 7.64, 3.92, 5.33, 4.85, 2.39, 4.16, 6.74,
3.53, 5.86, 5.41, 26.25, 4.40, 10.79, 7.08, 2.86, 33.92, 3.03, 0.98, 5.63, 4.89, 2.26, 10.49,
6.51, 7.36, 2.13, 6.45, 2.29, 21.15, 4.07, 4.34, 5.38, 7.69, 4.93]

### Minuit least squares fit
binned_hist, bins = np.histogram(data, bins=40, range=xrange)
bin_centers = bins[:-1] + np.diff(bins) / 2
data_yerr = [np.sqrt(x) for x in binned_hist]

least_squares = LeastSquares(bin_centers, binned_hist, data_yerr, f)

m = Minuit(least_squares, N=40, mean=np.mean(data), sigma=np.sqrt(np.var(data)))  # starting values for parameters

m.migrad()  # finds minimum of least_squares function
m.hesse()   # accurately computes uncertainties
