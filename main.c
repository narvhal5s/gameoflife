// Główny moduł sterujacy

//Jego podstawowym zadaniem jest wczytanie danych konfiguracyjnych
//Nastepnie bedzie wywoływał kolejne moduly

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char **argv){

	//deklaracja parametrow ktore zostana wczytane
		
	int width;
	int height;
	int gen_counter;
	int rand_gen_percent;
	char *save_to;
	char *load_from;
	char *rules;
	
	//przy podaniu jednego lub dwoch argumentow pierwszy jest traktowany jako pliku konfiguracyjny 
	// drugi opcjonalny jako dane wejsciowe

	if(argc <= 3){
		FILE *config= fopen(argv[1] , "r");
		if(config == NULL){
			printf("Podany plik konfiguracyjny %s nie istnieje, wczytane zostaną parametry domyslne\n" , argv[1]);
			width = 50;
			height = 50;
			gen_counter = 200;
			rand_gen_percent = 25;
			save_to = "txt";
			rules = "23/3";
		}
		else{
			printf("Otwarto plik konfiguracyjny %s , rozpocznam wczytywanie parametrow\n" , argv[1]);
		}
		fclose(config);
	}

	//Jeżeli podano wiecej argumetnow to program interpretuje je jako parametry konfiguracyjne podane w odpowiedniej kolejnosci

	else if( argc == 7){
		printf("Podane wsadowo parametry domyślne zostana wczytane\n");
		width = atoi(argv[1]);
		height = atoi(argv[2]);
		gen_counter = atoi(argv[3]);
		rand_gen_percent = atoi(argv[4]);
		save_to = argv[5];
		rules = argv[6]; 
	}

	//Jezeli powyzsze warunki sa niespelnione program wyswietla odpowiedni blad
	
	else{
		printf ("Podano nieprawidlowa liczbe argumenty wywolanie\n");
		printf ("Prosze podac nazwek pliku konfiguracyjnego albo dokladnie 6 parametrow\n");
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
	/* RAND OR FROM PNG OR FROM PNG
	if(argv[4]){
		printf("Argument width wykracza poza prawidlowy przedzial\nWczytano wartosc domyslna\n");
		width = 50 ; 
	}*/	
	if( strcmp(save_to , "png") != 0 && strcmp(save_to , "gif") != 0 && strcmp(save_to , "txt") != 0){
		printf("Argument save_to jest nieprawidlowy( prawidłowe: png,txt,gif)\nWczytano wartosc domyslna\n");
		save_to = "txt" ; 
	}
	// Ponizej weryfikacja poprawnosci parametru rules
	// Nastepuje rowniez przepisanie go na dwie tablice live i born
	// live zawiera liczbe sasiadow dla ktorej komorka zostaje zywa
	// born zawiera liczbe sasiadow dla ktorej komorka rodzi sie
	// Te dwie tablice zostana przekazane do modulu GAME, co stanowi zmiane wzgledem specyfikacji implementacyjnej
	int i ;
	int rules_check = 0 ;
	int live_counter = 0 ;
	for( i = 0 ; i < strlen(rules) ; i++ ){
		if( (rules[i] < '1' ||  rules[i] > '8')  && rules[i] != 'a' ){
			printf("Argument rules jest nieprawidlowy ");
			rules_check = 1 ;
			break;
		}
	}

	//Jezli parametr rules zawiera bledne dane wczytane zostana domyslne

	if(rules_check == 1){
		printf("Wczytano wartosc domyslna (23/3)\n");
		int live[2] = { 2 , 3 } ; 
		int born[1] = { 3 } ;
	}
	
	//Dane z prawidlowego parmetru rules zostana wczytane do dwoch tablic lokowanych dynamicznych 
	//W tym celu obliczono ilosc sasidow dla ktorzych komorka przezywa 

	else{
		for( i = 0 ; rules[i] != 'a' ; i++){
			live_counter++;
		}

		int *live = (int*)malloc( live_counter * sizeof(int)) ;
		int *born = (int*)malloc( ( strlen(rules) - live_counter -1 ) * sizeof(int)) ; 

		for( i = 0; rules[i] != 'a' ; i++ ){
			live[i] = rules[i] - '0';
		}

		int j;	
		for( i++ , j=0 ; i<strlen(rules) ; i++ , j++){
			born[j] = rules[i] - '0';
		}	
	
	}
	return 0;

}
