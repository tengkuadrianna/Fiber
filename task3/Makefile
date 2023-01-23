CC = g++
CFLAGS = -g #-fsanitize=address#-Wall -Wextra -Werror -pedantic -std=c++11

task1: task3.cpp ../context.o fiber.o
	$(CC) $(CFLAGS) -o task3 task3.cpp ../context.o fiber.o

fiber.o: fiber.hpp fiber.cpp
	$(CC) $(CFLAGS) -c fiber.cpp

context.o: ../context.hpp ../context.s
	$(CC) $(CFLAGS) -c ../context.s


clean:
	rm -f task1 task3 *.o