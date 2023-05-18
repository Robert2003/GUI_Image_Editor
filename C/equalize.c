// Copyright Damian Mihai-Robert 312CAb 2022-2023
#include "equalize.h"
#include "histogram.h"

// Functia care realizeaza egalizarea imaginii
void equlize(image img)
{
	long long ap[RGB_MAX + 1] = {0}, max = -1, sum;
	int width, height, area;

	if (img.image_loaded) {
		if (!strchr("25", img.magic_word[1])) {
			printf("Black and white image needed\n");
			return;
		}
		width = img.width;
		height = img.height;
	} else {
		printf("No image loaded\n");
		return;
	}

	// Creez vectorul de aparitii folosind un interval = 1, adica 256 bin-uri
	make_apparitions(img, ap, INTERVAL_LENGTH, &max);

	area = width * height;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			sum = 0;
			// Calculez valoarea noua a pixelului
			for (int k = 0; k <= img.data[i][j].grayscale; k++)
				sum += ap[k];
			img.data[i][j].grayscale = (double)sum / area * RGB_MAX;
		}
	printf("Equalize done\n");
}
