// Modul wczytujacy

#include "save.h"

int save_to_txt(Cell ***field , int width , int height){
	for(int i = 0 ; i < width ; i++){
		for(int j = 0 ; j < height ; j++){
			printf("%d " , field[i][j]->state);
		}
		printf("\n");
	}


}
