// Copyright Damian Mihai-Robert 312CAb 2022-2023
#include "save.h"

// Functia care salveaza o imagine sub format binar
void save_binary(image img, FILE *f)
{
	// Daca este P2 sau P3, va scrie P5, respectiv P6
	if (img.magic_word[1] <= '3')
		fprintf(f, "%c%c\n", img.magic_word[0], img.magic_word[1] + 3);
	else
		fprintf(f, "%s\n", img.magic_word);
	fprintf(f, "%d %d\n", img.width, img.height);
	fprintf(f, "%d\n", img.maxval);
	for (int i = 0; i < img.height; i++)
		for (int j = 0; j < img.width; j++)
			if (strchr("36", img.magic_word[1])) {
				fprintf(f, "%c", (UC)img.data[i][j].rgb.r);
				fprintf(f, "%c", (UC)img.data[i][j].rgb.g);
				fprintf(f, "%c", (UC)img.data[i][j].rgb.b);
			} else {
				fprintf(f, "%c", (UC)img.data[i][j].grayscale);
			}
}

// Functia care salveaza o imagine sub format text
void save_ascii(image img, FILE *f)
{
	if (img.magic_word[1] <= '3')
		fprintf(f, "%s\n", img.magic_word);
	else
		// Daca este P5 sau P6, va scrie P2, respectiv P3
		fprintf(f, "%c%c\n", img.magic_word[0], img.magic_word[1] - 3);
	fprintf(f, "%d %d\n", img.width, img.height);
	fprintf(f, "%d\n", img.maxval);
	for (int i = 0; i < img.height; i++)
		for (int j = 0; j < img.width; j++)
			if (strchr("36", img.magic_word[1])) {
				fprintf(f, "%d ", img.data[i][j].rgb.r);
				fprintf(f, "%d ", img.data[i][j].rgb.g);
				fprintf(f, "%d ", img.data[i][j].rgb.b);
			} else {
				fprintf(f, "%d ", img.data[i][j].grayscale);
			}
}

// Functia care realizeaza salvarea imaginii dintr-un format in oarecare altul
void save_image(image img)
{
	char file_name[LENGTH], save_type[LENGTH], ch;
	FILE *f;

	scanf("%s%c", file_name, &ch);
	if (ch != '\n') {
		scanf("%c", &ch);
		if (ch != '\n') {
			save_type[0] = ch;
			scanf("%s", save_type + 1);
		}
	}

	if (!img.image_loaded) {
		printf("No image loaded\n");
		return;
	}

	// Printez o imagine in format binar
	if (ch == '\n') {
		f = fopen(file_name, "wb");
		save_binary(img, f);
		fclose(f);
	} else {
		// Printez o imagine in format ascii
		if (!strcmp(save_type, "ascii")) {
			f = fopen(file_name, "wt");
			save_ascii(img, f);
			fclose(f);
		}
	}
	printf("Saved %s\n", file_name);
}
