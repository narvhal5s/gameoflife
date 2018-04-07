// Modul wczytujacy

#include "save.h"

int save_to_txt(Cell ***field , int width , int height){
	FILE *out = fopen("result.txt" , "wa");
	if(out == NULL){
		printf("Nie udalo sie utworzyc pliku z wynikami");
		return 1;
	}
	for(int i = 0 ; i < width ; i++){
		for(int j = 0 ; j < height ; j++){
			fprintf(out , "%d " , field[i][j]->state);
		}
		fprintf(out , "\n");
	}
	fclose(out);
	return 0;
}

int save_to_png(Cell ***field, int width , int height , int gen_number){
	
	unsigned char *image = malloc(width * height * 4 * sizeof(char)) ;
	int k = 0 ; 
	for( int i = 0 ; i < width ; i++ ){
		for( int j = 0 ; j < height ; j++ , k=k+4  ){
			if( field[i][j]->state == 1 ){
				image[k] = 0 ;
				image[k+1] = 0 ; 
				image[k+2] = 0 ;
			}
			else{
				image[k] = 255 ;
				image[k+1] = 255 ; 
				image[k+2] = 255 ;
			}
			image[k+3] = 255 ; 
		}
	}

	unsigned error = lodepng_encode32_file( "resulte.png" , image , width, height );

	if(error) 
		printf("error %u: %s\n", error, lodepng_error_text(error));
	
	free(image);	
	return 0 ;
}

int make_gif( int gen_counter ) {




	return 0 ; 
}
