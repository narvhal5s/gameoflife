#ifndef _FIELD_H
#define _FIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cell{
	int state;
	int neighbours;
} Cell;

//Funkcja obslugujaca caly modul field 
Cell *** field_control( int width , int height , char *load_type , char *load_detail );

//Funkcja tworzy pole gry
//Pole gry to dwuwymiarowa tablica wzkaznikow na strukture
Cell *** make_field(int width , int height );

//Funkcja zwalnia pamiec zaalokowana na stworzenie pola 
//Wzkaznik ***field zwroci NULL jesli wszystko zostanie prawidlowo zwolnione
Cell *** clear_field ( Cell ***field , int width , int height );

//Funkcje wczytujaca dane na pole gry , odpowiednio z pliku tekstowego obraz png i losowe 
Cell *** read_from_txt ( Cell *** field , int width , int height , char *load_detail); 


Cell *** read_from_png ( Cell *** field , int width , int height , char *load_detail); 


Cell *** fill_random ( Cell *** field , int width , int height , char *load_detail); 

#endif
