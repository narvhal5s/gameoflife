#ifndef _SAVE_H
#define _SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h> 
#include "field.h"

int save_to_txt( Cell ***field , int width , int height );
int save_to_png( Cell ***field , int width , int height , int gen_number );
int make_gif(int gen_counter); //Liczba generacji jest potrzebna bo tyle bedzie PNG
#endif
