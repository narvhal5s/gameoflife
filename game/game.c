
#include "game.h"

int play_game( Cell ***field , int width , int height , int *live ,int live_counter , int *born , int born_counter ,char *save_to , int gen_counter){


	field = count_neighbours( field , width, height ) ;


	field = change_state ( field ,  width , height , live , live_counter , born , born_counter) ;


	save_to_txt( field , width , height) ;	


	return 0;
}


Cell *** count_neighbours( Cell ***field , int width , int height ){

	int count_n = 0 ;
	int x , y ;  
	for(int i = 0 ; i < width   ; i++ ) {
		for(int j = 0 ; j < height  ; j++ ) {
			for( int k = i - 1 ; k <= i + 1 ; k++ ) {
				for( int l = j - 1 ; l <= j + 1 ; l++ ) {
					x = k;
					y = l;
					if(k == -1) 
						x = width - 1;
					if(l == -1)
						y = height - 1;
					if(k == width) 
						x = 0 ;
					if(l == height)
						y = 0 ;
					
					if( field[x][y]->state == 1)
						count_n++;
				}
			}
		if( field[i][j]->state == 1)
			count_n--;
		field[i][j]->neighbours = count_n;
		count_n = 0 ;
		}
	}
	return field;
} 


Cell *** change_state(Cell ***field , int width , int height , int *live , int live_counter , int *born , int born_counter){
	
	for(int i = 0 ; i < width   ; i++ ) {
		for(int j = 0 ; j < height  ; j++ ) {
			if(field[i][j]->state == 0){
				for(int b = 0 ; b < born_counter ; b ++){
					if(born[b] == field[i][j]->neighbours)
						field[i][j]->state = 1 ;
				}
			
			}
			if(field[i][j]->state == 1){
				int czy_zdycha = 1;
				for(int l = 0 ; l < live_counter ; l ++){
					if(live[l] == field[i][j]->neighbours)
						czy_zdycha = 0 ;
					
				}
				if(czy_zdycha)
					field[i][j]->state = 0 ; // zdechla	
			}
		}
	}	
	return field;
}

