// Główny moduł sterujacy

//Jego podstawowym zadaniem jest wczytanie danych konfiguracyjnych
//Nastepnie bedzie wywoływał kolejne moduly

#include "field/field.h"
#include "game/game.h" 

//char *config_load( char *line , char *looking_for); // Mala funkcja zalaczona do main ktora posluzy do wyluskania danych z pliku konfiguracyjnego

int main( int argc, char **argv){

	//deklaracja parametrow ktore zostana wczytane
		
	int width ;
	int height ;
	int gen_counter ;
	char *load_type ;
	char *load_detail ;
	char *save_to ;
	char *rules ;
	
	//przy podaniu jednego argument jest on traktowany jako pliku konfiguracyjny 

	if(argc == 2){
		FILE *config= fopen(argv[1] , "r");
		if(config == NULL){
			printf("Podany plik konfiguracyjny %s nie istnieje, wczytane zostaną parametry domyslne\n" , argv[1]);
			width = 50;
			height = 50;
			gen_counter = 200;
			load_type = "random" ;
			load_detail = "25" ;	
			save_to = "txt";
			rules = "23/3";
		}
		else{
			/*printf("Otwarto plik konfiguracyjny %s , rozpocznam wczytywanie parametrow\n" , argv[1]);
			width = 
			height = 
			gen_counter = 
			load_type =
			load_detail = 
			save_to =
			rules =*/
			fclose(config);
		}
	}

	//Jeżeli podano wiecej argumetnow to program interpretuje je jako parametry konfiguracyjne podane w odpowiedniej kolejnosci

	else if( argc == 8){
		printf("Podane wsadowo parametry domyślne zostana wczytane\n");
		width = atoi(argv[1]) ;
		height = atoi(argv[2]) ;
		gen_counter = atoi(argv[3]) ;
		load_type = argv[4] ;
		load_detail = argv[5] ;
		save_to = argv[6] ;
		rules = argv[7] ; 
	}

	//Jezeli powyzsze warunki sa niespelnione program wyswietla odpowiedni blad
	
	else{
		printf ("Podano nieprawidlowa liczbe argumenty wywolanie\n") ;
		printf ("Prosze podac nazwek pliku konfiguracyjnego albo dokladnie 7 parametrow\n") ;
		return 1 ;
	}


	//Sprawdzenie poprawnosci argumentow

	if(width > 300 || width < 1){
		printf("Argument width wykracza poza prawidlowy przedzial\nWczytano wartosc domyslna\n");
		width = 100 ; 
	}	
	if(height > 300 || height < 1){
		printf("Argument height wykracza poza prawidlowy przedzial\nWczytano wartosc domyslna\n");
		height = 100 ; 
	}	
	if(gen_counter > 1000 || gen_counter < 1){
		printf("Argument gen_counter wykracza poza prawidlowy przedzial\nWczytano wartosc domyslna\n");
		gen_counter = 200 ; 
	}	
	if(strcmp(load_type , "png") == 0 || strcmp(load_type , "txt") == 0 ){
		FILE *input = fopen( load_detail , "r");
		if( input == NULL){
			printf("Nie udalo sie otworzyc pliku %s, uzyty zostanie losowe wypelnienie planszy\n" , load_detail ) ;
			 load_type = "random" ;
			 load_detail = "25" ; 
		}
		else{
			fclose(input);
		}
	}
	else if( strcmp(load_type , "random") == 0 && atoi(load_detail) <=100 && atoi(load_detail) >= 0 ){
		;
	}
	else{
		printf("Nieprawidlowy argument load_type i/lub load_detail\n");
	}
	if( strcmp(save_to , "png") != 0 && strcmp(save_to , "gif") != 0 && strcmp(save_to , "txt") != 0){
		printf("Argument save_to jest nieprawidlowy( prawidłowe: png,txt,gif)\nWczytano wartosc domyslna\n");
		save_to = "txt" ; 
	}
	
	// Ponizej weryfikacja poprawnosci parametru rules
	// Nastepuje rowniez przepisanie go na dwie tablice live i born
	// live zawiera liczbe sasiadow dla ktorej komorka zostaje zywa
	// born zawiera liczbe sasiadow dla ktorej komorka rodzi sie
	// Te dwie tablice zostana przekazane do modulu GAME zamiast lancucha rules, co stanowi zmiane wzgledem specyfikacji implementacyjnej
	
	int rules_check = 0 ;
	int live_counter = 0 ;

	int i ;
	for( i = 0 ; i < strlen(rules) ; i++ ){
		if( (rules[i] < '0' ||  rules[i] > '8')  && rules[i] != '/' ){
			printf("Argument rules jest nieprawidlowy ");
			rules_check = 1 ;
			break;
		}
	}

	//Jezli parametr rules zawiera bledne dane zostanie zresetowny do domyslnych danych

	if(rules_check == 1){
		printf("Wczytano wartosc domyslna (23/3)\n");
		rules = "23/3";
	}
	
	//Dane rules zostana wczytane do dwoch tablic lokowanych dynamicznych 
	//W tym celu obliczono ilosc sasidow dla ktorych komorka przezywa live_counter i born_counter dla ilu sie rodzi

	for( i = 0 ; rules[i] != '/' ; i++)
		live_counter++;
	
	int *live = (int*)malloc( live_counter * sizeof(int)) ;
	int born_counter = strlen(rules) - live_counter -1 ;
	int *born = (int*)malloc( born_counter * sizeof(int)) ; 
	
	for( i = 0; rules[i] != '/' ; i++ )
		live[i] = rules[i] - '0';

	int j;	
	for( i++ , j=0 ; i<strlen(rules) ; i++ , j++)
		born[j] = rules[i] - '0';	
	
	//Wywolanie modulu field
	Cell ***field = field_control( width , height , load_type , load_detail );

	//Wywolanie modulu game 	
	play_game( field , width , height  , live , live_counter , born , born_counter , save_to , gen_counter);	

	//Finalizacja programu , sprzatanie
	field = clear_field( field , width , height ) ;
	free(live);
	free(born);
	return 0;

}
