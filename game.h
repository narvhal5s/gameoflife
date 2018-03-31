#ifndef _GAME_H
#define _GAME_H

#include "field.h"
#include "save.h"

int play_game( Cell ***field , int width , int height , int *live , int live_counter , int *born , int born_counter ,char *save_to , int gen_counter) ;
Cell *** count_neighbours( Cell ***field , int width , int height ) ; 
Cell *** change_state(Cell ***field , int width , int height , int *live , int live_counter , int *born , int born_counter);

#endif 
