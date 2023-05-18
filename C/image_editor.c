// Copyright Damian Mihai-Robert 312CAb 2022-2023
#include "my_library.h"

void read_commands(void)
{
	image img;
	coordinates selection;
	char command[LENGTH], filename[LENGTH], ch, filter[LENGTH];
	char filter_name[LENGTH];
	FILE *f;
	img.image_loaded = false;

	while (scanf("%s", command)) {
		if (!strcmp(command, "LOAD")) {
			load_utility(&f, command, filename, &img, &selection);
		} else if (!strcmp(command, "SELECT")) {
			select_region(img, &selection);
		} else if (!strcmp(command, "SAVE")) {
			save_image(img);
		} else if (!strcmp(command, "APPLY")) {
			scanf("%c", &ch);
			if (ch == '\n') {
				if (!img.image_loaded) {
					printf("No image loaded\n");
					return;
				}
				printf("Invalid command\n");
				return;
			}
			scanf("%s", filter_name);

			apply(&img, selection, filter_name);
		} else if (!strcmp(command, "CROP")) {
			crop(&img, &selection);
		} else if (!strcmp(command, "HISTOGRAM")) {
			histogram(img);
		} else if (!strcmp(command, "EQUALIZE")) {
			equlize(img);
		} else if (!strcmp(command, "EXIT")) {
			remove_photo(&img);
			break;
		} else if (!strcmp(command, "ROTATE")) {
			rotate(&img, &selection);
		} else {
			while (scanf("%c", &ch) && ch != '\n')
				;
			printf("Invalid command\n");
		}
	}
}

int main(void)
{
	read_commands();
	return 0;
}
