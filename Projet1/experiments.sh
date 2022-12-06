#!/bin/bash

N_MAX_THREAD=64

echo "Producer_Consumer"
echo "N,J,End"
for ((i=2; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./ProduceurConsumer ${i} 8192
    done
done

echo "Philosophes"
echo "N,J,End"
for ((i=1; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./Philo ${i}
    done
done

echo "Reader_Whriter"
echo "N,J,End"
for ((i=2; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./ReadWrite ${i}
    done
done


echo "Test_And_Set"
echo "N,J,End"
for ((i=1; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./TAS ${i}
    done
done


echo "Test_And_Test_And_Set"
echo "N,J,End"
for ((i=1; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./TTAS ${i}
    done
done

echo "My_Producer_Consumer"
echo "N,J,End"
for ((i=2; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./MyProduceurConsumer ${i} 8192
    done
done

echo "My_Philosophes"
echo "N,J,End"
for ((i=1; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./MyPhilo ${i}
    done
done

echo "My_Reader_Whriter"
echo "N,J,End"
for ((i=2; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./MyReadWrite ${i}
    done
done 


echo "Producer_Consumer_TTAS"
echo "N,J,End"
for ((i=2; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./ProduceurConsumerTTAS ${i} 8192
    done
done

echo "Philosophes_TTAS"
echo "N,J,End"
for ((i=1; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./PhiloTTAS ${i}
    done
done

echo "Reader_Whriter_TTAS"
echo "N,J,End"
for ((i=2; i <= $N_MAX_THREAD; i=i*2))
do
    for j in {1..5} 
    do
        /usr/bin/time -o /dev/stdout -f "${i}, ${j}, %e" bin/./ReadWriteTTAS ${i}
    done
done 

make clean