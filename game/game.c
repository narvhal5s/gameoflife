//Modul game przeprowadza kolejne generacja i wywoluje funkcje zapisu z modulu save
 
#include "game.h"

int play_game( Cell ***field , int width , int height , Rules rules ,char *save_to , int gen_counter){
	
	//Deklaracja zmienne ktora sprwadza czy zachodza zmiany przy generacji
	int change_checker = 1 ;

	//Petla wywolujaca kolejne generacje
	for( int i = 0 ; i < gen_counter ; i ++ ){

		//Zliczanie sasiadow poszczegolnych komorek
		field = count_neighbours( field , width, height ) ;

		//Zmiana stanow poszczegolnych komorek
		field = change_state ( field ,  width , height , rules , &change_checker ) ;
		//Jezeli zadanym wynikiem jest plik gif zapisywany jest obraz z kazdej generacji 
		if( strcmp ( save_to ,  "gif" ) == 0 ){
			save_to_png( field , width , height , i ) ;
		}
		
		//Jezeli zmienna jest prawdziwa to znaczy ze na planszy nie zachodza zmiany 
		//Nastepuje wyjscie z petli
		if( change_checker ) 
			break ;
	}
	
	//Zapis koncowej generacji w zadanym formacie 

	if( strcmp( save_to , "png" ) == 0 ) {
		save_to_png( field , width , height , gen_counter ) ;	
	}

	if( strcmp( save_to , "txt" ) == 0 ) {
		save_to_txt( field , width , height );
	}

	if( strcmp ( save_to ,  "gif" ) == 0 ){
		save_to_txt( field , width , height );
		make_gif( gen_counter ) ; 	
	}	
	
	
	return 0;
}


Cell *** count_neighbours( Cell ***field , int width , int height ){
	
	//Zmienna przechowujaca ilosc zywych sasiadow
	int count_n = 0 ;
	
	//Zmienne do laczenia krawedzi planszy
	int x , y ;  
	
	//Petle przechodzace po tablicy komorek 
	for(int i = 0 ; i < width   ; i++ ) {
		for(int j = 0 ; j < height  ; j++ ) {
			//Petle ktore przechodza po sasiadach danej komorki
			for( int k = i - 1 ; k <= i + 1 ; k++ ) {
				for( int l = j - 1 ; l <= j + 1 ; l++ ) {
					
					//Laczenie krawedzi planszy
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
					
					//Sprawdzenie czy sasiadnia komorka jest zywa
					if( field[x][y]->state == 1)
						count_n++;
				}
			}
		//Jezeli sprawdzana komorka jest zywa odejmuje ja od zliczonych
		if( field[i][j]->state == 1)
			count_n--;
		
		//Zapis ilosci zywych sasiadow do struktury
		field[i][j]->neighbours = count_n;
		
		//Zerowanie licznika 
		count_n = 0 ;
		
		}
	
	}
	
	return field;

} 


Cell *** change_state(Cell ***field , int width , int height , Rules rules , int *change_checker ){
	
	//Ustawienie zmiennej mowiacej o tym czy zachodza zmianny jezeli nie zajde to wlasnie bedzie zwrocona wartosc
	*change_checker = 1 ;
	
	//Zmienna do sprawdzenia czy komorka umrze
	int die ;
	
	//Petle przechodzace po tablicy komorek
	for(int i = 0 ; i < width   ; i++ ) {
		for(int j = 0 ; j < height  ; j++ ) {
			
			//Jezeli komorka jest martwa sprawdza czy ma liczbe sasiadow potrzbna zeby sie ozywic
			if(field[i][j]->state == 0){
				
				//Wykorzystana jest tablica zawierajaca liczbe sasiadow dla ktorych komorka sie rodzi 
				for(int b = 0 ; b < rules.born_counter ; b ++){
					if(rules.born[b] == field[i][j]->neighbours){
						field[i][j]->state = 1 ; //Komorka sie rodzi
						*change_checker = 0 ;
					}
				}
			
			}

			//Jezeli komorka jest zywa sprawdza czy umrze czy pozostanie zywa
			if(field[i][j]->state == 1){
				die = 1;
		
				//Wykorzystana jest tablica zawieajaca liczbe sasidaow dla ktorych komorka pozostaje zywa
				for(int l = 0 ; l < rules.live_counter ; l ++){
					if(rules.live[l] == field[i][j]->neighbours)
						die = 0 ;
					
				}
				if(die){
					*change_checker = 0 ;
					field[i][j]->state = 0 ; // Komorka umiera	
				}
			}
		}
	}	
	return field;
}

