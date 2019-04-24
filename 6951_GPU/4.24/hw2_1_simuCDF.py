import matplotlib.pyplot as plt
import numpy as np


data = np.loadtxt('simu_res.txt')

# Choose how many bins you want here
num_bins = 80

# Use the histogram function to bin the data
counts, bin_edges = np.histogram(data, bins=num_bins, normed=True)

# Now find the cdf
cdf = np.cumsum(counts)

# And finally plot the cdf
plt.plot(bin_edges[1:], cdf)


plt.xlabel('bin_edge')
plt.ylabel('cumulative distribution: 0 --- 1')
plt.yticks(np.arange(0, 1, 1.0))
plt.title('Inverse uniform var to get exp-distributed var CDF\n')
plt.show()

'''
import csv

x = []
y = []

with open('simu_res.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y.append(float(row[1]))

# , label='skitscat', color='k', s=25, marker="o"
plt.scatter(x,y, s=0.5)
plt.xlabel('simuNum for each thread')
plt.ylabel('simulation result')
plt.title('Inverse uniform simulation \n')
plt.legend()
plt.show()
'''