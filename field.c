//Moduł tworzący pole i wczytujacy dane

#include "field.h"


int field_control( int width , int height , char *load_type , char *load_detail ){
	
	Cell ***field = make_field( width , height );

	clear_field( field , width , height );
	
	return 0;

}

Cell *** make_field( int width , int height ){
	Cell ***field = malloc(width * sizeof(**field));
	for(int i=0 ; i< width ; i++)
		field[i] = malloc(height * sizeof(*field));
	
	for(int i=0 ; i< width ; i++)
		for(int j=0 ; j< height ; j++)
			field[i][j] = (Cell*)malloc(sizeof(Cell));
			
	return field;
}


Cell *** read_from_txt ( Cell *** field , int width , int height , char *load_detail){
	FILE *txt_file = fopen("load_detail" , "r");
	if(txt_file == NULL){
		printf("Ni udalo sie otworzyc pliku %s zawierajacego generacje" , load_detail ) ;
		return 1; 
	}
	

}

Cell *** read_from_png ( Cell *** field , int width , int height , char *load_detail){

}

Cell *** fill_random ( Cell *** field , int width , int height , char *load_detail){

}


int clear_field(Cell ***field , int width , int height){
	
	for(int i=0 ; i< width ; i++)
		for(int j=0 ; j< height ; j++)
			free(field[i][j]) ;

	for(int i=0 ; i< width ; i++)
		free(field[i]) ;

	free(field) ;

	return 0 ;  
} 
