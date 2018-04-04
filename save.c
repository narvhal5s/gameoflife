// Modul wczytujacy

#include "save.h"

int save_to_txt(Cell ***field , int width , int height){
	FILE *out = fopen("result.txt" , "w");
	if(out == NULL){
		printf("Nie udalo sie utworzyc pliku z wynikami");
		return 1;
	}
	int tmp = 0 ;
	for(int i = 0 ; i < width ; i++){
		for(int j = 0 ; j < height ; j++){
			fprintf(out , "%d " , field[i][j]->state);
			if(field[i][j]->state == 1 )
				tmp++;
		}
		fprintf(out , "\n");
	}
	fclose(out);
	printf("%d\n\n " ,  tmp ) ;
	return 0;
}

int save_to_png(Cell ***field, int width , int height , int gen_number){
	FILE *out = fopen("result.png_" , "w") ;
	if(out == NULL){
		printf("Nie udalo sie utworzyc pliku wynikowego") ; 
		return 1;
	}


	return 0 ;
}
