// Główny moduł sterujący

#include <stdio.h>
#include <png.h>

int main(int argc, char **argv){
	FILE *obrazek = fopen( "obrazek.png" , "rb");
	fread(0 , 1 , 8 , obrazek);
	if(png_sig_cmp( 0 , 0 , 8))
		printf ("NIE PNG");
	else
		printf ("PNG");
	return 0;
} 
