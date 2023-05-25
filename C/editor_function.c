/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#include "my_library.h"

void photo(char *filename, int angle, char *filter_name, char *save_path)
{
    image img;
    coordinates selection;
    FILE *f;
	img.image_loaded = false;

    load_utility(&f, "LOAD", filename, &img, &selection);
   	rotate(&img, &selection, angle);
    apply(&img, selection, filter_name);
	save_image(img, save_path, 'b');
	
	remove_photo(&img);
}
