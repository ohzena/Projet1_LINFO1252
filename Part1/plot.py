#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import csv

csv = pd.read_csv("csv/philo.csv", index_col=None)
print(csv)

# mean
csv.dropna(axis=0, how='any', subset=None, inplace=False)
mean = csv.groupby(["Num"]).mean()['End']
std = csv.groupby(["Num"]).std()['End']
threads = csv["Num"].unique()


fig1 = plt.figure()
plt.plot(threads, mean, color="pink", linewidth=1.0, linestyle="-.-")
plt.errorbar(threads, mean, yerr=std, fmt="-o")

plt.xlim(0,25)
plt.xticks(np.linspace(0,24,13))
plt.xlabel('Number of Threads')
plt.ylim(0, 1000)
plt.yticks(np.linspace(0, 1000, 11))

plt.ylabel("Mean Time[s]")
plt.title('Avgerage time of execution for n threads')
plt.savefig("plot_philo.png")

plt.show()

# Closing the plot.
plt.close()

