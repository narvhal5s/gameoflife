#include <stdio.h>
#include <png.h>

static png_structp png_ptr;
static png_infop info_ptr;

#define width_max 1000
#define height_max 1000

int main( int argc , char **argv){
	FILE *fp = fopen("pngtest.png", "rb");
	if (!fp)
	{
		return 1;
	}
	char header[8];
	fread(header, 1, 8, fp);
	int is_png = !png_sig_cmp(header, 0, 8);
	if (!is_png)
	{
		printf("NIE PNG\n");
		return 1;
	}
	printf("PNG\n");
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
		return 4;   /* out of memory */
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return 4;   /* out of memory */
	}			        
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr,
			(png_infopp)NULL);
		return 4;
	}
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);
	png_set_user_limits(png_ptr, width_max, height_max);
	png_read_info(png_ptr, info_ptr);
	return 0;
}

