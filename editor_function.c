#include "my_library.h"

void photo(char *filename, int angle, char *filter_name)
{
    image img;
    coordinates selection;
    FILE *f;

    load_utility(&f, "LOAD", filename, &img, &selection);

    if (angle == 180 || angle == -180)
		rotate_180(&img, selection, angle, true);
	else if (angle == 90 || angle == -270)
		rotate_90_clockwise(&img, &selection, angle);
	else if (angle == -90 || angle == 270)
		rotate_90_counter_clockwise(&img, &selection, angle);
	else if (angle == 360 || angle == -360 || angle == 0)
		printf("Rotated %d\n", angle);
	else
		printf("Unsupported rotation angle\n");

    apply(&img, selection, filter_name);
}