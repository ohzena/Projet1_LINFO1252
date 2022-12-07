all: philo p_and_c w_and_r tas ttas my_philo my_p_and_c my_w_and_r my_philo_ttas my_p_and_c_ttas my_w_and_r_ttas 

p_and_c: Part1/producerConsumer.c
	@gcc -Wall -o bin/ProduceurConsumer -pthread Part1/producerConsumer.c
	
philo: Part1/philosophe.c
	@gcc -Wall -o bin/Philo -pthread Part1/philosophe.c

w_and_r: Part1/reader_writer.c
	@gcc -Wall -o bin/ReadWrite -pthread Part1/reader_writer.c

tas: Part2/test_and_set.c
	@gcc -Wall -o bin/TAS -pthread Part2/test_and_set.c

ttas: Part2/test_and_test_and_set.c
	@gcc -Wall -o bin/TTAS -pthread Part2/test_and_test_and_set.c
	
my_p_and_c: Part2/myproducerConsumer.c
	@gcc -Wall -o bin/MyProduceurConsumer -pthread Part2/myproducerConsumer.c

my_philo: Part2/myphilosophe.c
	@gcc -Wall -o bin/MyPhilo -pthread Part2/myphilosophe.c

my_w_and_r: Part2/myreader_writer.c
	@gcc -Wall -o bin/MyReadWrite -pthread Part2/myreader_writer.c

my_p_and_c_ttas: Part2/producerConsumer_ttas.c
	@gcc -Wall -o bin/ProduceurConsumerTTAS -pthread Part2/producerConsumer_ttas.c

my_philo_ttas: Part2/philosophe_ttas.c
	@gcc -Wall -o bin/PhiloTTAS -pthread Part2/philosophe_ttas.c

my_w_and_r_ttas: Part2/reader_writer_ttas.c
	@gcc -Wall -o bin/ReadWriteTTAS -pthread Part2/reader_writer_ttas.c

clean:
	@rm bin/*
