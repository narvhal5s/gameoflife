// Modul zapisujacy dane

#include "save.h"


int save_to_txt(Cell ***field , int width , int height){
	
	//Utworzenie pliku wynikowego 
	FILE *out = fopen("result.txt" , "wa");
	if(out == NULL){
		printf("Nie udalo sie utworzyc pliku z wynikami");
		return 1;
	}
	
	//Petla przechodzi po tablicy i wypisuje wartosc stanu komorki
	for(int i = 0 ; i < width ; i++){
		for(int j = 0 ; j < height ; j++){
			fprintf(out , "%d " , field[i][j]->state);
		}
		fprintf(out , "\n");
	}
	fclose(out);
	return 0;
}

int save_to_png(Cell ***field, int width , int height , int gen_number , unsigned char *image ){

	//Pomocnicza zmienna iteracyjna, przeskakuje ona do kolejncyh czterech wartosci RGBA 	
	int k = 0 ; 

	//Petla przechodzi po tablicy, zywe komorki beda czarne , martwe biale
	for( int i = 0 ; i < width ; i++ ){
		for( int j = 0 ; j < height ; j++ , k=k+4  ){
			if( field[i][j]->state == 1 ){
				image[k] = 255 ;
				image[k+1] = 20 ; 
				image[k+2] = 147 ;
			}
			else{
				image[k] = 0 ;
				image[k+1] = 0 ; 
				image[k+2] = 0 ;
			}
			image[k+3] = 255 ; 
		}
	}

	//Zmienna do generowania kolejncych nazw plikow PNG
	char filename[20] ; 
	snprintf( filename , 20 , "image%03d.png" , gen_number ) ;
	
	//Wywolanie funkcji zapisu modulu lodepng
	unsigned error = lodepng_encode32_file( filename , image , width, height );

	if(error) 
		printf("error %u: %s\n", error, lodepng_error_text(error));
	return 0 ;
}

int make_gif() {

	system( "convert -delay 15 -loop 0 *.png mygif.gif" ) ;
	system( "rm *.png" ) ; 


	return 0 ; 
}
