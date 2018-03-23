

game: main.o
	$(CC) main.o -o game

main.o: main.c
	$(CC) main.c -c

filetest: game
	./game config.txt

commandtest: game
	./game 25 25 150 random 44  gif 13/5

commandtesterror: game
	./game 500 699 0 txa lak.png gidA 9a/1

memorytest: game
	valgrind -v ./game config.txt
