#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

#creation du jeu de donné

#jeu de donné POSIX
philo = pd.read_csv("csv/philo.csv")
pro_cons = pd.read_csv("csv/pro_con.csv")
rw = pd.read_csv("csv/rw.csv")
#jeu de donné TAS
tas = pd.read_csv("csv/test_and_set.csv")
my_philo = pd.read_csv("csv/my_philo.csv")
my_pro_cons = pd.read_csv("csv/my_pro_con.csv")
my_rw = pd.read_csv("csv/my_rw.csv")
#jeu de donné TTAS
ttas = pd.read_csv("csv/test_and_test_and_set.csv")
philo_ttas = pd.read_csv("csv/philo_ttas.csv")
pro_cons_ttas = pd.read_csv("csv/pro_cons_ttas.csv")
rw_ttas = pd.read_csv("csv/rw_ttas.csv")

def plot(csv1, csv2, csv3, titre, name1, name2, name3):
    #mean and std for function part1
    csv1.dropna(axis=0,  thresh=None, subset=None, inplace=False)
    mean = csv1.groupby("N")['End'].mean()
    std = csv1.groupby("N")['End'].std()
    threads = csv1["N"].unique()

    #mean and std for function TAS
    csv2.dropna(axis=0,  thresh=None, subset=None, inplace=False)
    my_mean = csv2.groupby("N")['End'].mean()
    my_std = csv2.groupby("N")['End'].std()
    my_threads = csv2["N"].unique()    

    #mean and std for function TTAS
    csv3.dropna(axis=0,  thresh=None, subset=None, inplace=False)
    mean_ttas = csv3.groupby("N")['End'].mean()
    std_ttas = csv3.groupby("N")['End'].std()
    threads_ttas = csv3["N"].unique()  

    #creation du graphe
    fig = plt.figure()
    ax = plt.subplot()

    POSIX = range(0,len(threads))
    TAS = range(0,len(my_threads))
    TTAS = range(0,len(threads_ttas))
    plt.errorbar(POSIX, mean, yerr=std, fmt='.-', capsize=5, label=name1)
    plt.errorbar(TAS , my_mean, yerr=my_std, fmt='.-', capsize=5, label=name2)
    plt.errorbar(TTAS, mean_ttas, yerr=std_ttas, fmt='.-', capsize=5, label=name3)

    ax.set_xlim(0, len(threads))
    ax.set_xticks(range(len(threads)))
    ax.set_xticklabels(threads)
    ax.set_ylim(0, 1.1*(mean_ttas.max() + std_ttas.max()))
 
    plt.legend()

    #nom des axes et titres 
    plt.xlabel('Nombre de Threads')
    plt.ylabel("Temps[s]")
    plt.title("Temps moyen d'exécution par n threads pour "  + titre)
  
    plt.grid(True)
    plt.savefig("Produceur_Consumer" + ".png")
    #plt.show()
    plt.close()

#Création des plots
#plot(philo, my_philo, philo_ttas, "Philosophes","POSIX", "TAS", "TTAS")
#plot(rw, my_rw, rw_ttas,"Reader/Writer", "POSIX", "TAS", "TTAS")
plot(pro_cons, my_pro_cons, pro_cons_ttas,"Produceur/Consumer", "POSIX", "TAS", "TTAS")
#plot(tas, ttas, ttas, "Test-And(-Test-And)-Set", "TAS", "", "TTAS")
