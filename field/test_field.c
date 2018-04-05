//Miejsce na testy modulu field


#include "field.h" 

#define WIDTH 40
#define HEIGHT 40
#define LOAD_TYPE "random"
#define LOAD_DETAIL "50"



int main( int argc , char *argv ){

	Cell *** field = field_control( WIDTH , HEIGHT , LOAD_TYPE , LOAD_DETAIL ) ;
	
	
	for(int i = 0 ; i < WIDTH ; i++ ){
		for(int j = 0 ; j < HEIGHT ; j++ ){
			printf("%d " , field[i][j]->state );
		}
		printf("\n");
	}

	field = clear_field( field , WIDTH , HEIGHT ) ; 

	if(field == NULL){
		printf("Czyszczenie pamieci zakonczone\n");
		return 0 ;
	}
	else
		printf("Wystapil blad podczas czyszczenia pamiec\n");
		return 1 ; 
}
