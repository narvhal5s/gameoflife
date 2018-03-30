// Główny moduł sterujacy

//Jego podstawowym zadaniem jest wczytanie danych konfiguracyjnych
//Nastepnie bedzie wywoływał kolejne moduly

#include "field.h"
#include "game.h" 

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
			printf("Otwarto plik konfiguracyjny %s , rozpocznam wczytywanie parametrow\n" , argv[1]);
			char buffor[50];
			width = atoi(fgets( buffor , 50 , config)) ;
			height = atoi(fgets( buffor , 50 , config)) ;
			gen_counter = atoi(fgets(buffor , 50 , config)) ;
			
			//Tutaj jest niedobrze, ale kiedy bedzie dobrze
			//Albo nie bedzie wgl nic i chuj
			/*load_type = fgets( buffor , 50 , config) ;
			load_detail = fgets( buffor , 50 , congif) ;
			save_to = fgets( buffor , 50 , config );
			rules = fgets( buffor , 50 , config) ;*/
		}
		fclose(config);
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

	if(width > 100 || width < 1){
		printf("Argument width wykracza poza prawidlowy przedzial\nWczytano wartosc domyslna\n");
		width = 50 ; 
	}	
	if(height > 100 || height < 1){
		printf("Argument height wykracza poza prawidlowy przedzial\nWczytano wartosc domyslna\n");
		height = 50 ; 
	}	
	if(gen_counter > 1000 || gen_counter < 1){
		printf("Argument gen_counter wykracza poza prawidlowy przedzial\nWczytano wartosc domyslna\n");
		gen_counter = 200 ; 
	}	
	if(strcmp(load_type , "png") == 0 || strcmp(load_type , "txt") == 0 ){
		FILE *input = NULL;
		input = fopen(load_detail , "r");
		if( input == NULL){
			printf("Nie udalo sie otworzyc pliku %s, uzyty zostanie losowe wypelnienie planszy\n" , load_detail ) ;
			load_type == "random" ;
			load_detail == "25" ; 
		}
		fclose(input);
	}
	else if( strcmp(load_type , "random") == 0 && atoi(load_detail) <=100 && atoi(load_detail) >= 0 ){
		printf("Wczytano random genracji %s\n" , load_detail);
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
	// Te dwie tablice zostana przekazane do modulu GAME zamiast lanucha rules, co stanowi zmiane wzgledem specyfikacji implementacyjnej
	
	int rules_check = 0 ;
	int live_counter = 0 ;

	int i ;
	for( i = 0 ; i < strlen(rules) ; i++ ){
		if( (rules[i] < '1' ||  rules[i] > '8')  && rules[i] != '/' ){
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
	//W tym celu obliczono ilosc sasidow dla ktorzych komorka przezywa live_counter 	

	for( i = 0 ; rules[i] != '/' ; i++)
		live_counter++;
	
	int *live = (int*)malloc( live_counter * sizeof(int)) ;
	int *born = (int*)malloc( ( strlen(rules) - live_counter -1 ) * sizeof(int)) ; 
	
	for( i = 0; rules[i] != '/' ; i++ )
		live[i] = rules[i] - '0';

	int j;	
	for( i++ , j=0 ; i<strlen(rules) ; i++ , j++)
		born[j] = rules[i] - '0';	
	
	//Wywolanie modulu field
	Cell ***field = field_control( width , height , load_type , load_detail );
	
	// Tutaj dzieja sie male testy i inne dziwne rzeczy 
	printf("WYnik%d\n" , play_game( field , height , width , born , live , save_to , gen_counter));	
	save_to_txt( field , width , height ) ;

	//Finalizacja programu , sprzatanie
	clear_field( field , height , width ) ;
	free(live);
	free(born);
	return 0;

}
