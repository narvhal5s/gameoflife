

game: main.o field.o save.o game.o
	@$(CC) main.o field.o save.o game.o -o game
	@rm *.o
main.o: main.c field.h game.h
	@$(CC) main.c -c -Wall

field.o: field.c field.h 
	@$(CC) field.c -c -Wall

save.o: save.c save.h field.h
	@$(CC) save.c -c -Wall

game.o: game.c game.h save.h field.h
	@$(CC) game.c -c -Wall


commandtest: game
	./game 50 50 150 random 100 gif 13/5

commandtesterror: game
	./game 500 699 0 txa lak.png gidA 9a/1

memorytest: game
	valgrind -v ./game 100 100 150 random 44  gif 13/5

txttest: game
	./game 5 6 150 txt matrix.txt  gif 23/3

memorytxttest: game
	valgrind -v  ./game 5 6 150 txt matrix.txt  gif 23/3

