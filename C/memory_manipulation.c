/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#include "memory_manipulation.h"

// Functie care aloca memorie pentru o matrice ascii si returneaza adresa ei
pixel **alloc_matrix(int width, int height)
{
	pixel **img = NULL;
	img = (pixel **)malloc(height * sizeof(pixel *));
	if (!img) {
		free(img);
		return NULL;
	}
	for (int i = 0; i < height; i++) {
		img[i] = (pixel *)calloc(width, sizeof(pixel));
		if (!img[i]) {
			free_matrix(img, i);
			return NULL;
		}
	}
	return img;
}

// Functie care dealoca memoria pentru o matrice
void free_matrix(pixel **mat, int n)
{
	for (int i = 0; i < n; i++)
		free(mat[i]);
	free(mat);
	mat = NULL;
}

// Functie care elibereaza matricea unei imagini
void remove_photo(image *img)
{
	if (img->image_loaded)
		free_matrix(img->data, img->height);
	else
		printf("No image loaded\n");
}
