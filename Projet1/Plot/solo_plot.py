#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

#creation du jeu de donné

#jeu de donné POSIX
philo = pd.read_csv("csv/philo.csv")
pro_cons = pd.read_csv("csv/pro_con.csv")
rw = pd.read_csv("csv/rw.csv")

def plot(csv1, titre, name1):
    #mean and std for function part1
    csv1.dropna(axis=0,  thresh=None, subset=None, inplace=False)
    mean = csv1.groupby("N")['End'].mean()
    std = csv1.groupby("N")['End'].std()
    threads = csv1["N"].unique()


    #creation du graphe
    fig = plt.figure()
    ax = plt.subplot()

    POSIX = range(0,len(threads))
    plt.errorbar(POSIX, mean, yerr=std, fmt='.-', capsize=5, label=name1)


    ax.set_xlim(0, len(threads))
    ax.set_xticks(range(len(threads)))
    ax.set_xticklabels(threads)
    ax.set_ylim(0, 1.1*(mean.max() + std.max()))
 
    plt.legend()

    #nom des axes et titres 
    plt.xlabel('Nombre de Threads')
    plt.ylabel("Temps[s]")
    plt.title("Temps moyen d'exécution par n threads pour "   + titre)
  
    plt.grid(True)
    #plt.savefig(titre +".png")
    plt.show()
    plt.close()

#Création des plots
plot(philo, "Philo_seule","POSIX")
plot(rw, "Reader_Writer_seule", "POSIX")
plot(pro_cons,"Produceur_Consumer_seule", "POSIX")
