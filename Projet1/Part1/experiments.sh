#!/bin/bash
echo "Producer_Consumer"
echo "N, J, Start, End"
for i in {2..64} 
do
    for j in {1..5} 
    do
        #Start=$(date +%s.%N)
        /usr/bin/time -f "${i}, ${j}, %e" bin/./ProduceurConsumer ${i} 8192
        #bin/./ProduceurConsumer ${i} 8192
        #End=$(date +%s.%N)
    done
done

echo "Philosophes"
echo "N, J, Start, End"
for i in {1..64} 
do
    for j in {1..5} 
    do
        #Start=$(date +%s.%N)
        /usr/bin/time -f "${i}, ${j}, %e" bin/./Philo ${i}
        #bin/./Philo ${i}
        #End=$(date +%s.%N)
        #echo "${i}, ${j}, ${Start}, ${End}"
    done
done

echo "Reader_Whriter"
echo "N, J, Start, End"
for i in {2..64} 
do
    for j in {1..5} 
    do
        #Start=$(date +%s.%N)
        #bin/./ReadWrite ${i}
        /usr/bin/time -f "${i}, ${j}, %e" bin/./ReadWrite ${i}
        #End=$(date +%s.%N)
        #echo "${i}, ${j}, ${Start}, ${End}"
    done
done
make clean