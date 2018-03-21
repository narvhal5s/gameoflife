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

	if(argc == 2 || argc == 3){
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
		printf ("Podano nieprawidlowe argumenty wywolanie\n");
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
	// RAND OR FROM PNG OR FROM PNG
	if(argv[4]){
		printf("Argument width wykracza poza prawidlowy przedzial\nWczytano wartosc domyslna\n");
		width = 50 ; 
	}	
	if( strcmp(save_to , "png") != 0 && strcmp(save_to , "gif") != 0 && strcmp(save_to , "txt") != 0){
		printf("Argument save_to jest nieprawidlowy( prawidłowe: png,txt,gif)\nWczytano wartosc domyslna\n");
		save_to = "txt" ; 
	}
	//if(rules) 	
	//Przepisanie char *rules na dwie tablice int *live int *born 
	

	return 0;

}
