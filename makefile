

play_life: main.o field.o save.o game.o lodepng.o
	@$(CC) main.o field.o save.o game.o  -o play_life
	@rm *.o
main.o: main.c field/field.h game/game.h
	@$(CC) main.c -c -Wall

field.o: field/field.c field/field.h lodepng/lodepng.h
	@$(CC) field/field.c -c -Wall

save.o: save/save.c save/save.h field/field.h lodepng/lodepng.h
	@$(CC) save/save.c -c  -Wall 

game.o: game/game.c game/game.h save/save.h field/field.h
	@$(CC) game/game.c -c -Wall

lodepng.o: lodepng/lodepng.c lodepng/lodepng.h
	@$(CC) lodepng/lodepng.c -c -Wall

commandtest: play_life
	./play_life 50 50 150 random 100 gif 13/5

commandtesterror: play_life
	./play_life 500 699 0 txt lak.png gidA 9a/1

memorytest: play_life
	valgrind -v ./play_life 100 100 150 random 44  gif 13/5

txttest: play_life
	./play_life 5 6 150 txt resources/matrix.txt  gif 23/3

memorytxttest: play_life
	valgrind -v  ./play_life 5 6 150 txt matrix.txt  gif 23/3

