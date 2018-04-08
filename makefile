

play_life: main.o field.o save.o game.o lodepng.o
	@$(CC) main.o field.o save.o game.o lodepng.o  -o play_life
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



commandtesterror: play_life
	./play_life 500 699 0 txt lak.png gidA 9a/1

memorytest: play_life
	valgrind -v ./play_life 100 100 150 random 44  txt 13/5

txttest: play_life
	./play_life 5 6 150 txt resources/matrix.txt  gif 23/3

txtsample: play_life
	./play_life 50 50 1 random 60 txt 23/3

pngtest: play_life
	./play_life 20 20 150 png resources/sample.png png 23/3

giftest: play_life
	./play_life 100 100 400 random 25 gif 23/3

pngmemorytest: play_life
	valgrind ./play_life 100 100 50 random 30 gif 23/3



glider: play_life
	./play_life 50 50 250 txt resources/glider.txt gif 23/3

chaos: play_life
	./play_life 50 50 250 txt resources/glider.txt gif 1/1

labirynty:
	./play_life 100 100 200 random 10 gif 12345/3

statki_1:
	./play_life 100 100 200 random 10 gif 234/3

miasto:
	./play_life 300 300 200 random 45 gif 2345/45678

conwaybig:
	./play_life 250 250 300 random 30 gif 23/3

continue_gen:
	./play_life 300 300 200 txt for_continue.txt  gif 23/3

ameba:
	./play_life 250 250 300 txt ./resources/probka.txt gif 1/1
