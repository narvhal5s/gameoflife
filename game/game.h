#ifndef _GAME_H
#define _GAME_H

#include "../field/field.h"
#include "../save/save.h"

//Funkcja sterujaca przeprowadzaniem kolejncych interacji , odwoluje sie do modulu save w celu zapisu danych
int play_game( Cell ***field , int width , int height , int *live , int live_counter , int *born , int born_counter ,char *save_to , int gen_counter) ;

//Funkcja zlicza sasiadow kazdej komorki
Cell *** count_neighbours( Cell ***field , int width , int height ) ; 

//Funkcja zmienia stan komorki w zaleznosci od liczby sasiadow
Cell *** change_state(Cell ***field , int width , int height , int *live , int live_counter , int *born , int born_counter , int *change_checker);

#endif 
