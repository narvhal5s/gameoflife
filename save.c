// Modul wczytujacy

#include "save.h"

int save_to_txt(Cell ***field , int width , int height){
	FILE *out = fopen("result.txt" , "w");
	if(out == NULL){
		printf("Nie udalo sie utworzyc pliku z wynikami");
		return 1;
	}
	int licznik = 0 ;
	for(int i = 0 ; i < width ; i++){
		for(int j = 0 ; j < height ; j++){
			fprintf(out , "%d " , field[i][j]->state);
			if(field[i][j]->state == 1)
				licznik++;
		}
		fprintf(out , "\n");
	}
	printf("%d\n" , licznik); 
	fclose(out);
	return 0;
}
