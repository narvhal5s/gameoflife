

game: main.o field.o
	$(CC) main.o field.o -o game

main.o: main.c field.h
	$(CC) main.c -c

field.o: field.c field.h 
	$(CC) field.c -c

filetest: game
	./game config.txt

commandtest: game
	./game 25 25 150 random 44  gif 13/5

commandtesterror: game
	./game 500 699 0 txa lak.png gidA 9a/1

memorytest: game
	valgrind -v ./game 25 25 150 random 44  gif 13/5
