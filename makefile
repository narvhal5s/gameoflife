

game: main.o field.o save.o
	$(CC) main.o field.o save.o -o game

main.o: main.c field.h save.h
	$(CC) main.c -c

field.o: field.c field.h 
	$(CC) field.c -c

save.o: save.c save.h field.h
	$(CC) save.c -c

filetest: game
	./game config.txt

commandtest: game
	./game 100 100 150 random 10  gif 13/5

commandtesterror: game
	./game 500 699 0 txa lak.png gidA 9a/1

memorytest: game
	valgrind -v ./game 25 25 150 random 44  gif 13/5

txttest: game
	./game 5 5 150 txt matrix.txt  gif 23/3
memorytxttest: game
	valgrind -v  ./game 5 5 150 txt matrix.txt  gif 23/3
