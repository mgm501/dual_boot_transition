import scipy.stats as scs
import numpy as np

probability  = scs.poisson.cdf(10,15.7)
#print(probability)

#Problem 3
# Part (a)
mean = 5
sigma = (5 * 0.68)
left_tail = scs.norm.cdf(mean - sigma * 1.23, loc=mean, scale=sigma)
right_tail = scs.norm.sf(mean + sigma * 1.23, loc=mean, scale=sigma)
print(left_tail + right_tail)
#print(1-gaussian_approx)

# Part (b)
#mean = 5
#sigma = (mean * 0.68)
right_distribution = scs.norm.sf(mean + sigma * 2.43, loc=mean, scale=sigma)
print(right_distribution)

#Part (c)
between_dis_up = scs.norm.cdf(mean + (sigma * 1.5), loc=mean, scale=sigma) - scs.norm.cdf(mean + (sigma * 0.5), loc=mean, scale=sigma)
between_dis_low = - scs.norm.cdf(mean - (sigma * 1.5), loc=mean, scale=sigma) + scs.norm.cdf(mean - (sigma * 0.5), loc=mean, scale=sigma)
print(between_dis_up + between_dis_low)

#Part (d)
above = scs.norm.cdf(mean + (sigma * 2.1), loc=mean, scale=sigma) - scs.norm.cdf(mean - (sigma * 1.2), loc=mean, scale=sigma)
print(above)

#Part (e)
std = scs.norm.ppf(.5)
print(std)

#Part (f)
std1 = scs.norm.ppf(.99)
print(std1)
