#!/bin/bash

echo "Producer_Consumer"
echo "N,J,End"
for i in {2..64} 
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./ProduceurConsumer ${i} 8192
    done
done

echo "Philosophes"
echo "N,J,End"
for i in {1..64} 
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./Philo ${i}
    done
done

echo "Reader_Whriter"
echo "N,J,End"
for i in {2..64} 
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./ReadWrite ${i}
    done
done
make clean