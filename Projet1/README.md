## Projet1_SINC1252
Programmation multi-threadée et évaluation de performances

Projet qui permet d'évaluer et expliquer la performance d’applications utilisant plusieurs threads et des primitives de synchronisation : mutex, sémaphores (première partie) ainsi que les verrous avec attente active, que nous avons implémenté nous même.
Les trois modèles utilisant plusieurs fil d'exécution sont le producteur-consommateur, les philosophes et le lecteur-écrivain. Chacun de ces modèles possède 3 versions différenciées pas leurs primitives de synchronisation. Les premières utilisent celles disponible dans la librairie pthread et sont disponibles dans le dossier Part1. Les secondes et troisièmes sont disponibles dans la Part2 et utilisent respectivement l'algorithme test-and-set et test-and-test-set. Les code c commencant par "my" sont implémentés avec test-and-set et ceux qui teminent par "_ttas.c" sont les dernières versions de nos trois modèles.

## Tool

```bash
#compile les codes c dans le dossier bin
make

#efface les codes compilés
make clean

#exécutes 5 fois chaque code avec différents nombre de thread (2,4,8,16,32,64) et récupère leurs temps d'exécution dans la sortie standart et effasse les codes compilés.
bash experiments.sh

#création des graphes de comparaison des 3 différents primitives. /!\ dans le dossier Plot
python3 plot.py

#création des graphes pour les 3 modèles multithread avec les primitives de la librairie posix /!\ dans le dossier Plot
python3 solo_plot.py
```


## Usage

Etre sur une machine LINUX qui possède le compilateur gcc.

/!\ Un système d'exploitation de type macOS avec une infrastructure M1 ne compilera pas le code
    même au travers d'une machine virtuelle.

```python3
pip install matplotlib
pip install numpy
pip install pandas
```

## Auteurs
Tia Benita (benita.tia@student.uclouvain.be)
Halliez Simon (simon.halliez@student.uclouvain.be)

