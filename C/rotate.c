/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#include "rotate.h"
#include "memory_manipulation.h"
#include "selection.h"

// Functie care inverseaza coloanele unei matrice delimitate de o selectie
void reverse_columns(image *img, coordinates selection)
{
	int x, y, width, height;

	x = selection.top_left.x;
	y = selection.top_left.y;
	width = selection.width;
	height = selection.height;

	for (int i = x; i <= x + (height - 1) / 2; i++)
		for (int j = y; j < y + width; j++)
			swap(&img->data[i][j], &img->data[2 * x + height - i - 1][j],
				 sizeof(img->data[i][j]));
}

// Functie care inverseaza liniile unei matrice delimitate de o selectie
void reverse_lines(image *img, coordinates selection)
{
	int x, y, width, height;

	x = selection.top_left.x;
	y = selection.top_left.y;
	width = selection.width;
	height = selection.height;

	for (int i = x; i < x + height; i++)
		for (int j = y; j <= y + (width - 1) / 2; j++)
			swap(&img->data[i][j], &img->data[i][2 * y + width - j - 1],
				 sizeof(img->data[i][j]));
}

// Functie care face transpusa unei matrice delimitate de o selectie
void transpose(image *img, coordinates selection)
{
	int x, y, height;

	x = selection.top_left.x;
	y = selection.top_left.y;
	height = selection.height;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < i; j++)
			swap(&img->data[i + x][j + y], &img->data[j + x][i + y],
				 sizeof(img->data[i + x][j + y]));
}

// Functia care intoarce o amtrice la 180 de grade
void rotate_180(image *img, coordinates selection, int angle,
				bool print)
{
	int width, height;

	width = selection.width;
	height = selection.height;

	if ((width != img->width || height != img->height) && width != height) {
		printf("The selection must be square\n");
		return;
	}

	/*
	Pentru a intoarce o matrice la 180 de grade trebuie sa inversam liniile
	si coloanele acesteia
	*/
	reverse_lines(img, selection);
	reverse_columns(img, selection);

	if (print)
		printf("Rotated %d\n", angle);
}

// Functia care intoarce o matrice la 90 de grade spre stanga
void rotate_90_counter_clockwise(image *img, coordinates *selection, int angle)
{
	int width, height;
	bool rotate_photo = false;

	width = selection->width;
	height = selection->height;

	if (width != img->width || height != img->height) {
		if (width != height) {
			printf("The selection must be square\n");
			return;
		}
	} else if (width == img->width && height == img->height) {
		rotate_photo = true;
	}

	/*
	Daca rotate este false, trebuie intoarsa o selectie la 90 de grade, adica
	trebuie creata transpusa + inversarea coloanelor
	*/
	if (!rotate_photo) {
		transpose(img, *selection);
		reverse_columns(img, *selection);
	// Daca trebuie intoarsa o imagine intreaga, creez una noua
	} else {
		pixel **new_img = alloc_matrix(height, width);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				memcpy(&new_img[i][j], &img->data[j][width - i - 1],
					   sizeof(img->data[i][j]));
		// Inlocuiesc matricea veche, interschimb width cu height
		remove_photo(img);
		swap(&img->height, &img->width, sizeof(img->height));
		swap(&selection->height, &selection->width, sizeof(img->height));
		img->data = new_img;
	}
	printf("Rotated %d\n", angle);
}

// Functia care intoarce o matrice la 90 de grade spre dreapta
void rotate_90_clockwise(image *img, coordinates *selection, int angle)
{
	int width, height;
	bool rotate_photo = false;

	width = selection->width;
	height = selection->height;

	if (width != img->width || height != img->height) {
		if (width != height) {
			printf("The selection must be square\n");
			return;
		}
	} else if (width == img->width && height == img->height) {
		rotate_photo = true;
	}

	/*
	Daca rotate este false, trebuie intoarsa o selectie la -90 de grade, adica
	trebuie creata transpusa + inversarea liniilor
	*/
	if (!rotate_photo) {
		transpose(img, *selection);
		reverse_lines(img, *selection);
	// Daca trebuie intoarsa o imagine intreaga, creez ouna noua
	} else {
		pixel **new_img = alloc_matrix(height, width);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				memcpy(&new_img[i][j], &img->data[height - j - 1][i],
					   sizeof(img->data[i][j]));
		// Inlocuiesc matricea veche, interschimb width cu height
		remove_photo(img);
		swap(&img->height, &img->width, sizeof(img->height));
		swap(&selection->height, &selection->width, sizeof(img->height));
		img->data = new_img;
	}
	printf("Rotated %d\n", angle);
}

/*
Functia care realizeaza rotirea imaginii la 0, +-90, +-180, +-270, +-360 grade
*/
void rotate(image *img, coordinates *selection, int angle)
{
	if (!img->image_loaded) {
		printf("No image loaded\n");
		return;
	}
	if (angle == 180 || angle == -180)
		rotate_180(img, *selection, angle, true);
	else if (angle == 90 || angle == -270)
		rotate_90_clockwise(img, selection, angle);
	else if (angle == -90 || angle == 270)
		rotate_90_counter_clockwise(img, selection, angle);
	else if (angle == 360 || angle == -360 || angle == 0)
		printf("Rotated %d\n", angle);
	else
		printf("Unsupported rotation angle\n");
}
