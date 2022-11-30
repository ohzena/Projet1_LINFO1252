#!/bin/bash

echo "Producer_Consumer"
echo "N,J,End"
for ((i=2; i <= 64; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./ProduceurConsumer ${i} 8192
    done
done

echo "Philosophes"
echo "N,J,End"
for ((i=1; i <= 64; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./Philo ${i}
    done
done

echo "Reader_Whriter"
echo "N,J,End"
for ((i=1; i <= 64; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./ReadWrite ${i}
    done
done
make clean
