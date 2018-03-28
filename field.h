#ifndef _FIELD_C
#define _FIELD_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell{
	int state;
	int neighbours;
} Cell;


int field_control( int width , int height , char *load_type , char *load_detail );
Cell *** make_field(int width , int height );
int clear_field ( Cell ***field , int width , int height );
Cell *** read_from_txt ( Cell *** field , int width , int height , char *load_detail); 
Cell *** read_from_png ( Cell *** field , int width , int height , char *load_detail); 
Cell *** fill_random ( Cell *** field , int width , int height , char *load_detail); 

#endif
