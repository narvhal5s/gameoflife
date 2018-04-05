#ifndef _SAVE_H
#define _SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include <zlib.h>
#include "../field/field.h"

//Zapis do pliku txt 
int save_to_txt( Cell ***field , int width , int height );

//Zapis do obrazu PNG w przypadku generacji gif zostaje jeden obraz z ktorego mozna kontynuowac generacje
int save_to_png( Cell ***field , int width , int height , int gen_number );

//Generuje pliku gif zajmuje sie rownierz wyczyszczeniem plikow PNG
int make_gif(int gen_counter); //Liczba generacji jest potrzebna bo tyle bedzie PNG

#endif
