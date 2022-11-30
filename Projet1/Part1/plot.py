#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd



#creation du jeu de donné
philo = pd.read_csv("csv/philo.csv")
pro_cons = pd.read_csv("csv/pro_con.csv")
rw = pd.read_csv("csv/rw.csv")

def plot(csv, name):
    #mean and std
    csv.dropna(axis=0,  thresh=None, subset=None, inplace=False)
    mean = csv.groupby("N")['End'].mean()
    std = csv.groupby("N")['End'].std()
    threads = csv["N"].unique()

    #creation du graphe
    fig = plt.figure()
    ax = plt.subplot()

    first = range(0,len(threads))
    plt.errorbar(first, mean, yerr=std, fmt='.-', capsize=5, label=name)


    ax.set_xlim(0, len(threads))
    ax.set_xticks(range(len(threads)))
    ax.set_xticklabels(threads)
    ax.set_ylim(0, 1.1*(mean.max() + std.max()))
 
    #plt.plot(threads, mean, label= "Average " + name)
    #plt.plot(threads, std, label="Standard error " + name)
    plt.legend()

    #nom des axes et titres 
    plt.xlabel('Number of Threads')
    plt.ylabel("Average Time[s]")
    plt.title('Avgerage time of execution for n threads for ' + name)
  
    plt.grid(True)
    plt.savefig(name + ".png")
    plt.show()
    plt.close()

#Création des plots
plot(philo, "Philosophe")
plot(rw, "Reader_Writer")
plot(pro_cons, "Produceur_Consumer")
