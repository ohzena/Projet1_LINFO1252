#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd



#creation du jeu de donné
philo = pd.read_csv("csv/philo.csv", index_col=None)
procons = pd.read_csv("csv/pro_con.csv", index_col=None)
rw = pd.read_csv("csv/rw.csv", index_col=None)
#print(philo)
#print(procons)
#print(rw)

def plot(csv, name):
    #creation du jeu de donné
    csv.dropna(axis=0,  thresh=None, subset=None, inplace=False)
    mean = csv.groupby("N")['End'].mean()
    std = csv.groupby("N")['End'].std()
    threads = csv["N"].unique()

    fig = plt.figure()
    X = range(0,len(threads), 1)
    plt.errorbar(X, mean, std, fmt='.-', capsize=5, ecolor='black', label=name)
    plt.xlim(0, len(threads)+1)
    plt.xticks(threads)
    plt.ylim(bottom=0, top = 1.1*(mean.max() + std.max()))

    plt.plot(threads, mean, color="pink", linewidth=1.0, linestyle="-")
    plt.legend()

    #nom des axes et titres 
    plt.xlabel('Number of Threads')
    plt.ylabel("Average Time[s]")
    plt.title('Avgerage time of execution for n threads for ' + name)
  
    plt.grid(True)
    plt.savefig(name + ".png")
    plt.show()
    plt.close()

plot(philo, "Philosophe")
plot(rw, "Reader_Writer")
plot(procons, "Produceur_Consumer")
