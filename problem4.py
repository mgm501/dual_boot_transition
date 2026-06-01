import numpy as np
import scipy
import matplotlib.pyplot as plt

x = np.linspace(0,20,100)
average = []
otheraverage = []

firstmean = 8.6
secondmean = 7.7

firstvar = 4.3
secondvar = 6.7

for i in range(100):
  #y = np.random.default_rng().random(10)
  mean = np.random.normal(loc=firstmean, scale=firstvar, size=10)
  mean2 = np.random.normal(loc=secondmean, scale=secondvar, size=10)
  sample_mean = np.mean(mean)
  sample_mean2 = np.mean(mean2)
  if sample_mean < 0:
    sample_mean = 0
  if sample_mean2 < 0:
    sample_mean2 = 0
  average.append(sample_mean)
  otheraverage.append(sample_mean2)

var = np.sqrt(np.var(average))
bootstrap_first_av = np.mean(average)
othervar = np.sqrt(np.var(otheraverage))
bootstrap_second_av = np.mean(otheraverage)
plt.hist(average, x, label="first distribution")
#plt.show()
plt.xlabel("Sampled Mean Value")
plt.ylabel("Counts")

plt.axvline(bootstrap_first_av - var, color='blue', linestyle='dashed',linewidth=2)
plt.axvline(var + bootstrap_first_av, color='blue', linestyle='dashed',linewidth=2)
plt.axvline(bootstrap_first_av - 2*var, color='blue', linestyle='dashed',linewidth=2)
plt.axvline(2*var + bootstrap_first_av, color='blue', linestyle='dashed',linewidth=2)


plt.axvline(bootstrap_second_av - othervar, color='orange', linestyle='dashed', linewidth=2)
plt.axvline(othervar + bootstrap_second_av, color='orange', linestyle='dashed',linewidth=2)
plt.axvline(bootstrap_second_av - 2*othervar, color='orange', linestyle='dashed', linewidth=2)
plt.axvline(2*othervar + bootstrap_second_av, color='orange', linestyle='dashed',linewidth=2)

plt.axvline(bootstrap_first_av, color='blue', linestyle='dashed',linewidth=2)
plt.axvline(bootstrap_second_av, color='orange', linestyle='dashed',linewidth=2)

plt.hist(otheraverage, x, label="second distribution")
plt.legend(loc='upper left')
plt.show()
