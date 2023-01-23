CC = g++
CFLAGS = -g -O0 #-fsanitize=address#-Wall -Wextra -Werror -pedantic -std=c++11

task1: task2.1.cpp ../context.o fiber.o
	$(CC) $(CFLAGS) -o task1 task2.1.cpp ../context.o

task2: task2.2.cpp ../context.o fiber.o
	$(CC) $(CFLAGS) -o task2 fiber.o task2.2.cpp ../context.o

fiber.o: fiber.hpp fiber.cpp
	$(CC) $(CFLAGS) -c fiber.cpp

context.o: ../context.hpp ../context.s
	$(CC) $(CFLAGS) -c ../context.s


clean:
	rm -f task1 task2 *.o ../context.o