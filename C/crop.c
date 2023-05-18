// Copyright Damian Mihai-Robert 312CAb 2022-2023
#include "crop.h"
#include "memory_manipulation.h"
#include "selection.h"

// Functia care realizeaza crop pe o selectie
void crop(image *img, coordinates *selection)
{
	// Variabile pentru a scurta liniile de cod
	int x = selection->top_left.x, y = selection->top_left.y;
	int width = selection->width, height = selection->height;

	if (img->image_loaded) {
		// Auxiliara pentru programare defensiva
		pixel **new_img = alloc_matrix(width, height);
		if (!new_img)
			return;
		for (int i = x; i < x + height; i++) {
			for (int j = y; j < y + width; j++) {
				if (strchr("36", img->magic_word[1]))
					new_img[i - x][j - y].rgb = img->data[i][j].rgb;
				else
					new_img[i - x][j - y].grayscale = img->data[i][j].grayscale;
			}
		}
		// Inlocuiesc matricea veche cu cea cropped
		remove_photo(img);
		img->width = width;
		img->height = height;
		img->data = new_img;
		printf("Image cropped\n");
	} else {
		printf("No image loaded\n");
		return;
	}
	// Selectez toata imaginea la final
	select_all(*img, selection, true);
}
