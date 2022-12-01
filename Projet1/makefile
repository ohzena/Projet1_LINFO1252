all: philo p_and_c w_and_r  tas ttas  my_philo my_p_and_c my_w_and_r  my_philo_ttac my_p_and_c_ttac my_w_and_r_ttac 

p_and_c: Part1/code/producerConsumer.c
	@gcc -Wall -o bin/ProduceurConsumer -pthread Part1/code/producerConsumer.c
	
philo: Part1/code/philosophe.c
	@gcc -Wall -o bin/Philo -pthread Part1/code/philosophe.c

w_and_r: Part1/code/reader_writer.c
	@gcc -Wall -o bin/ReadWrite -pthread Part1/code/reader_writer.c

tac: Part2/code/test_and_set.c
	@gcc -Wall -o bin/TAS -pthread Part2/code/test_and_set.c

ttac: Part2/code/test_and_test_and_set.c
	@gcc -Wall -o bin/TTAS -pthread Part2/code/test_and_test_and_set.c
	
my_p_and_c: Part2/code/myproducerConsumer.c
	@gcc -Wall -o bin/MyProduceurConsumer -pthread Part2/code/myproducerConsumer.c

my_philo: Part2/code/myphilosophe.c
	@gcc -Wall -o bin/MyPhilo -pthread Part2/code/myphilosophe.c

my_w_and_r: Part2/code/myreader_writer.c
	@gcc -Wall -o bin/MyReadWrite -pthread Part2/code/myreader_writer.c

my_p_and_c_ttac: Part2/code/producerConsumer_ttac.c
	@gcc -Wall -o bin/ProduceurConsumerTTAS -pthread Part2/code/producerConsumer_ttas.c

my_philo_ttac: Part2/code/philosophe_ttas.c
	@gcc -Wall -o bin/PhiloTTAS -pthread Part2/code/philosophe_ttas.c

my_w_and_r_ttac: Part2/code/reader_writer_ttac.c
	@gcc -Wall -o bin/ReadWriteTTAS -pthread Part2/code/reader_writer_ttas.c

clean:
	@rm bin/*
