
#include "field.h"


Cell *** field_control( int width , int height , char *load_type , char *load_detail ){

	//Inicjalizacja pola gry 	
	
	Cell ***field = make_field( width , height );

	//W zaleznosci od parametru load_type wywolane zostana rozne funkcje
	
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
	
	char c ;
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

	return field;
}

Cell *** fill_random ( Cell *** field , int width , int height , char *load_detail){
	
	//Zmienn do losowej generacji
	
	time_t tt;

	srand(time(&tt));

	int percent = atoi(load_detail);
	
	//Generacji losowa, odchylenie w zaleznosci od wielkosci pola gry 
	//Mimo nie najwiekszej precyzji dziala sprawnie i jest prost 	
	
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


Cell *** clear_field(Cell ***field , int width , int height){
	
	//Zwolnienie pamieci w kolejnosci odwrotnej do rezerwowania

	for(int i=0 ; i< width ; i++)
		for(int j=0 ; j< height ; j++)
			free(field[i][j]) ;

	for(int i=0 ; i< width ; i++)
		free(field[i]) ;

	free(field) ;

	field = NULL ; 

	return field ;
} 
