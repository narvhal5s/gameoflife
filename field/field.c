
#include "field.h"

Cell *** field_control( int width , int height , char *load_type , char *load_detail ){

	//Inicjalizacja pola gry 	
	
	Cell ***field = make_field( width , height );

	//W zaleznosci od parametru load_type wywolane zostana rozne funkcje do wypelniania pola gry
	
	if(strcmp(load_type , "txt") == 0)
		field = read_from_txt( field , width , height , load_detail);
	
	else if(strcmp(load_type , "random") == 0)
		field = fill_random( field , width , height , load_detail);
	
	else if(strcmp(load_type , "png") == 0)
		field = read_from_png( field , width , height , load_detail);
	
	return field ; 

}

Cell *** make_field( int width , int height ){
	
	//Zarezerwowanie miejsca na wskazniki do odpowiednich komorek
	
	Cell ***field = malloc(width * sizeof(**field));
	
	for(int i=0 ; i< width ; i++)
		field[i] = malloc(height * sizeof(*field));
	
	//Zarezerwownie miejsca dla poszczegolnych komorek pola
	
	for(int i=0 ; i< width ; i++)
		for(int j=0 ; j< height ; j++)
			field[i][j] = (Cell*)malloc(sizeof(Cell));
	
	//Wartosci poszczegolnych komorek sa zerowane
	
	for(int i=0 ; i < width ; i++){
		for(int j=0 ; j < height ; j++){
				field[i][j]->state = 0 ;
				field[i][j]->neighbours = 0 ;
		}
	}
	
	return field;
}


Cell *** read_from_txt ( Cell *** field , int width , int height , char *load_detail){
	
	//Otwarcie pliku do wczytania, bez weryfikacji poprawnosci, zostala ona wykonan w module main
	
	FILE *txt_file = fopen( load_detail , "r" );
	
	//Zmienne potrzebne do wczytywania
	
	char c = 0  ;
	int i = 0 , j = 0 ;
	
	//Petla while wczytuje az do konca pliku 
	
	while( c != EOF ){
		c = fgetc( txt_file ) ;
		if(c == '1' || c == '0'){
			field[i][j]->state = c - '0' ;
			field[i][j]->neighbours = 0 ;
			j++;
		}
		else if( c ==  ' ' );
		else if( c ==  '\t' );
		else if( c ==  EOF );
		else if( c == '\n' ){
			i++;
			j = 0;
		}
		else{
			printf("Napotkano niezanany znak w pliku %s\n " , load_detail ) ;
			break;
		}

	}
	
	fclose(txt_file);

	return field ; 
}

Cell *** read_from_png ( Cell *** field , int width , int height , char *load_detail){
	
	//Deklaracja zmiennych potrzebnych modulowi lodepng
	unsigned error;
	unsigned char *image;
	unsigned t_width = width , t_height = height ;
	unsigned char *png ;
	size_t png_size ;
	
	//Dwufazowe wczytywanie obrazu PNG
	error = lodepng_load_file ( &png , &png_size , load_detail ) ;
	if(!error) 
		error = lodepng_decode32( &image , &t_width , &t_height , png , png_size) ;
	if(error)
		printf("Error %u: %s\n" , error , lodepng_error_text(error) ) ;

	free(png) ;
	
	//Wynikiem tego jest tablica image ktora zawiera wartosci R G B A dla kolejnych bitow
	
	int k = 0 ; 
	
	//Petla przepisuje tablice image na strukture CELL
	for(int i=0 ; i < width ; i++){
		for(int j=0  ; j < height ; j++ , k=k+4 ){
			
			//Kazdy czarny pixel zostanie potraktowany jako zywa komorka 
			if( image[k] == 0 && image[k+1] == 0 && image[k+2] == 0)
				field[i][j]->state = 1 ;
			
			//Pozostale kolory sa traktowane jako martwa
			else
				field[i][j]->state = 0 ;
		}
	}

	free(image) ;
	return field;
}

Cell *** fill_random ( Cell *** field , int width , int height , char *load_detail){
	
	//Zmienn do losowej generacji
	
	time_t tt;

	srand(time(&tt));

	int percent = atoi(load_detail);
	
	//Generacji losowa, odchylenie w zaleznosci od wielkosci pola gry 
	//Mimo nie najwiekszej precyzji dziala sprawnie i jest prosta 	
	
	for(int i=0 ; i < width ; i++){
		for(int j=0 ; j < height ; j++){
			if( rand()%101 < percent )
				field[i][j]->state = 1 ;
			else
				field[i][j]->state = 0 ;
		}
	}

	return field;
}


int clear_memory(Cell ***field , int width , int height , Rules rules ){
	
	//Zwolnienie pamieci w kolejnosci odwrotnej do rezerwowania

	for(int i=0 ; i< width ; i++)
		for(int j=0 ; j< height ; j++)
			free(field[i][j]) ;

	for(int i=0 ; i< width ; i++)
		free(field[i]) ;

	free( rules.live ) ;
	free( rules.born ) ;

	free(field) ;

	return 0 ;
} 
	
Rules read_rules( char *loaded_rules , Rules rules ){
	
	
	//Dane loaded_rules zostana wczytane do dwoch tablic lokowanych dynamicznych 
	//W tym celu obliczono ilosc sasidow dla ktorych komorka przezywa live_counter i born_counter dla ilu sie rodzi
	// live zawiera liczbe sasiadow dla ktorej komorka zostaje zywa
	// born zawiera liczbe sasiadow dla ktorej komorka rodzi sie
	
	int i , j ;
	
	rules.live_counter = 0 ; 	
	rules.born_counter = 0 ;
	
	for( i = 0 ; loaded_rules[i] != '/' ; i++)
		rules.live_counter++;
	
	rules.live = (int*)malloc( rules.live_counter * sizeof(int)) ;
	rules.born_counter = strlen(loaded_rules) - rules.live_counter -1 ;
	rules.born = (int*)malloc( rules.born_counter * sizeof(int)) ; 
	
	for( i = 0; loaded_rules[i] != '/' ; i++ )
		rules.live[i] = loaded_rules[i] - '0';

	for( i++ , j=0 ; i<strlen(loaded_rules) ; i++ , j++)
		rules.born[j] = loaded_rules[i] - '0';	
	
	return rules ; 

}
