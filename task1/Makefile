CC = g++
CFLAGS = -g -Wall #-fsanitize=address -fsanitize=undefined -std=c++11

task1: task1.1.cpp ../context.o
	$(CC) $(CFLAGS) -o task1 task1.1.cpp ../context.o

task2: task1.2.cpp ../context.o
	$(CC) $(CFLAGS) -o task2 task1.2.cpp ../context.o


context.o: ../context.hpp ../context.s
	$(CC) $(CFLAGS) -c ../context.s


clean:
	rm -f task1 task2 *.o ../context.o