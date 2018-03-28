
#include "field.h"


Cell *** field_control( int width , int height , char *load_type , char *load_detail ){
	
	Cell ***field = make_field( width , height );

	field = fill_random( field , width , height , load_detail);
	
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
			
	return field;
}


Cell *** read_from_txt ( Cell *** field , int width , int height , char *load_detail){
	FILE *txt_file = fopen( load_detail , "r" );
	if(txt_file == NULL){
		printf("Nie udalo sie otworzyc pliku %s zawierajacego generacje" , load_detail ) ;
	}
	char c = 'c';
	int i = 0 , j = 0 ;
	while( c != EOF ){
		c = fgetc( txt_file ) ;
		if(c == '1' || c == '0'){
			field[i][j]->state = c - '0' ;
			j++;
		}
		else if( c ==  ' ' );
		else if( c == '\n' ){
			i++;
			j = 0;
		}
		else{
			break;
		}
	}
	fclose(txt_file);
	return field ; 
}

Cell *** read_from_png ( Cell *** field , int width , int height , char *load_detail){

}

Cell *** fill_random ( Cell *** field , int width , int height , char *load_detail){
	time_t tt;
	srand(time(&tt));
	int random_variable;
	for(int i=0 ; i< width ; i++){
		for(int j=0 ; j < height ; j++){
			random_variable = rand()%101;
			if(random_variable <= atoi(load_detail) - 1)
				field[i][j]->state = 1 ;
			else
				field[i][j]->state = 0 ;
		}
	}

	return field;
}


int clear_field(Cell ***field , int width , int height){
	
	//Zwolnienie pamieci odwrotnie do jej zarezerwowania

	for(int i=0 ; i< width ; i++)
		for(int j=0 ; j< height ; j++)
			free(field[i][j]) ;

	for(int i=0 ; i< width ; i++)
		free(field[i]) ;

	free(field) ;

} 
