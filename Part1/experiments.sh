#!/bin/bash
mkdir -p csv
echo "Producer_Consumer"
echo "N, J, Start, End" >> csv/pro_con.csv
for i in {2..64} 
do
    for j in {1..5} 
    do
        Start=$(date +%s.%N)
        bin/./ProduceurConsumer ${i} 8192
        End=$(date +%s.%N)
        echo "${i}, ${j}, ${Start}, ${End}" >> csv/pro_con.csv
    done
done

echo "Philosophes"
echo "N, J, Start, End" >> philo.csv
for i in {1..64} 
do
    for j in {1..5} 
    do
        Start=$(date +%s.%N)
        bin/./Philo ${i}
        End=$(date +%s.%N)
        echo "${i}, ${j}, ${Start}, ${End}" >> csv/philo.csv
    done
done

echo "Reader_Whriter"
echo "N, J, Start, End" >> csv/rw.csv
for i in {2..64} 
do
    for j in {1..5} 
    do
        Start=$(date +%s.%N)
        bin/./ReadWrite ${i}
        End=$(date +%s.%N)
        echo "${i}, ${j}, ${Start}, ${End}" >> csv/rw.csv
    done
done