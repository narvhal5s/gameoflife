//Miejsce na testy modulu field


#include "field.h" 


//Zmienne uzywane do tesow w module field Obok podano jakie wartosci moga one przyjac 

#define WIDTH 20  //Zakres od 1 do 100
#define HEIGHT 20 //Zakres od 1 do 100
#define LOAD_TYPE "random" // random lub txt lub png
#define LOAD_DETAIL "50" //Dla random zakres od 0-100 dla txt i png sciezka do pliku 



int main( int argc , char *argv ){

	//Zainicjowanie pola
	Cell *** field = field_control( WIDTH , HEIGHT , LOAD_TYPE , LOAD_DETAIL ) ;
	
	//Wudruk na ekran konsoli
	int live_cell_counter = 0; //Wzbogacony o zliczanie zywych komorek, przydatny w testach losowej generacji

	for(int i = 0 ; i < WIDTH ; i++ ){
		for(int j = 0 ; j < HEIGHT ; j++ ){

			if(field[i][j]->state == 1)
				live_cell_counter++ ;

			printf("%d " , field[i][j]->state );
		}

		printf("\n");

	}
	
	//Wypis na konsole zywych komorek i procentu calosci diagnostyka funkcji fill_random

	printf("Ilosc zywych komorek na planszy wynosi: %d\n" , live_cell_counter) ;

	printf("Stanowi to %.2f procent wszystkich komorek\n" , (float)live_cell_counter/(WIDTH * HEIGHT)*100 );


	//Czyszczenie pamieci

	if(field == NULL){
		printf("Czyszczenie pamieci zakonczone\n");
		return 0 ;
	}
	else{
		printf("Wystapil blad podczas czyszczenia pamiec\n");
		return 1 ; 
	}
}

