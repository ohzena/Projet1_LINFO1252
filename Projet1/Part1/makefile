all: philo p_and_c w_and_r

p_and_c: code/producerConsumer.c
	@gcc -Wall -o bin/ProduceurConsumer -pthread code/producerConsumer.c
	
philo: code/philosophe.c
	@gcc -Wall -o bin/Philo -pthread code/philosophe.c

w_and_r: code/reader_writer.c
	@gcc -Wall -o bin/ReadWrite -pthread code/reader_writer.c

clean:
	@rm bin/*
