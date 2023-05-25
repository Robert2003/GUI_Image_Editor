/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#include "filters.h"
#include "memory_manipulation.h"

// Cele 4 kerneluri
const double edge_detection[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
const double sharpen[] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
const double box_blur[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
const double gaussian_blur[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

// Vectorii utilizati pentru o zona de 3x3 pixeli, ca la algoritmul lui Lee
const int lin[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int col[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

int clamp_number(int *x)
{
	if (*x < MIN)
		return MIN;
	if (*x > MAX)
		return MAX;
	return *x;
}

// Functia care face clamp la valorile unui pixel
void clamp(pixel **new_img, coordinates selection)
{
	int width = selection.width, height = selection.height;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			new_img[i][j].rgb.r = clamp_number(&new_img[i][j].rgb.r);
			new_img[i][j].rgb.g = clamp_number(&new_img[i][j].rgb.g);
			new_img[i][j].rgb.b = clamp_number(&new_img[i][j].rgb.b);
		}
}

// Functia care aplica un filtru asupra unei selectii
void apply_filter(image *img, coordinates selection, const double *filter,
				  double multiply)
{
	int x = selection.top_left.x, y = selection.top_left.y;
	int width = selection.width, height = selection.height;

	// Matrice auxiliara in care vor fi stocate noile valori ale pixelilor
	pixel **new_img = NULL;
	new_img = alloc_matrix(width, height);
	if (!new_img)
		return;

	for (int i = x; i < x + height; i++) {
		for (int j = y; j < y + width; j++) {
			if (!(i <= 0 || i >= img->height - 1 || j <= 0 ||
				  j >= img->width - 1)) {
				/*
				Parcurg toti vecinii unui pixel, inclusiv pe el si calculez
				noile valori
				*/
				for (int k = 0; k < 9; k++) {
					new_img[i - x][j - y].rgb.r +=
						img->data[i + lin[k]][j + col[k]].rgb.r * filter[k];
					new_img[i - x][j - y].rgb.g +=
						img->data[i + lin[k]][j + col[k]].rgb.g * filter[k];
					new_img[i - x][j - y].rgb.b +=
						img->data[i + lin[k]][j + col[k]].rgb.b * filter[k];
				}
			}
		}
	}
	if (fabs(multiply - 1) < 0.0001)
		clamp(new_img, selection);
	// Copiez valorile din matricea auxiliara in imaginea initiala
	for (int i = x; i < x + height; i++)
		for (int j = y; j < y + width; j++) {
			if (!(i <= 0 || i >= img->height - 1 || j <= 0 ||
				  j >= img->width - 1)) {
				img->data[i][j].rgb.r = multiply * new_img[i - x][j - y].rgb.r;
				img->data[i][j].rgb.g = multiply * new_img[i - x][j - y].rgb.g;
				img->data[i][j].rgb.b = multiply * new_img[i - x][j - y].rgb.b;
			}
		}
	// Eliberez memorie matricei auxiliara
	free_matrix(new_img, height);
	new_img = NULL;
}

// Functia care citeste parametrul comenzii APPLY si apeleaza filtrul necesar
void apply(image *img, coordinates selection, char *filter_name)
{
	const double *filter;
	double multiply = 1.0;

	/*
	Variabila filter este un pointer spre unul din kernel-uri pentru a avea un
	singur apel al functiei de aplicare filtru
	*/
	if (!strcmp(filter_name, "EDGE")) {
		filter = edge_detection;
	} else if (!strcmp(filter_name, "SHARPEN")) {
		filter = sharpen;
	} else if (!strcmp(filter_name, "BLUR")) {
		filter = box_blur;
		multiply = 1.0 / 9.0;
	} else if (!strcmp(filter_name, "GAUSSIAN_BLUR")) {
		filter = gaussian_blur;
		multiply = 1.0 / 16.0;
	} else {
		printf("APPLY parameter invalid\n");
		return;
	}

	if (img->image_loaded && !strchr("36", img->magic_word[1])) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	if (!img->image_loaded) {
		printf("No image loaded\n");
		return;
	}

	apply_filter(img, selection, filter, multiply);
	printf("APPLY %s done\n", filter_name);
}
