#ifndef _FIELD_H
#define _FIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Podstawowa struktura jednej komorki
typedef struct cell{
	int state; //Stan w jakim sie znajduje 1 - zywa lub 0 -martwa
	int neighbours; //Liczba zywych sasiadow komorki zakres od 0 do 8 wlacznie
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

//Funkcja wczytuje dane z obrazu PNG
Cell *** read_from_png ( Cell *** field , int width , int height , char *load_detail); 

//Funkcja wypelnia stany komorek losowo z procentem okreslonym przez uzytkownika
//Odczylenie od tej wartosci wynosi do 5%
Cell *** fill_random ( Cell *** field , int width , int height , char *load_detail); 

#endif
