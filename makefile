

all: main.o
	$(CC) main.o -o game

main.o: main.c
	$(CC) main.c -c

filetest: game
	./game config.txt

commandtest: game
	./game 25 25 150 f gif 13

memorytest: game
	valgrind ./game 25 25 150 f gif 13
