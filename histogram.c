// Copyright Damian Mihai-Robert 312CAb 2022-2023
#include "histogram.h"

/*
Functie care creaaza un vector de aparitii, facand grupe de cate interval_len
numere. Aparitiile numerelor care apartin aceleiasi grupe se cumuleaza
*/
void make_apparitions(image img, ll ap[], int interval_len, ll *max)
{
	int width, height;
	width = img.width;
		height = img.height;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			ap[img.data[i][j].grayscale / interval_len]++;
			if (ap[img.data[i][j].grayscale / interval_len] > (*max))
				(*max) = ap[img.data[i][j].grayscale / interval_len];
		}
}

// Functie care realizeaza histograma unei imagini
void histogram(image img)
{
	int interval_len, stars, bins, x, cnt = 0;
	long long ap[RGB_MAX + 1] = {0}, max = -1;
	char ch;

	scanf("%c", &ch);
	if (ch != ' ') {
		if (!img.image_loaded) {
			printf("No image loaded\n");
			return;
		}
		printf("Invalid command\n");
		return;
	}

	// Citesc parametrii comenzii
	do {
		scanf("%d%c", &x, &ch);
		cnt++;
		if (cnt == 1)
			stars = x;
		if (cnt == 2)
			bins = x;
	} while (ch != '\n');

	// Verific sa fie exact 2 parametri, altfel este functie invalida
	if (cnt != 2) {
		if (!img.image_loaded) {
			printf("No image loaded\n");
			return;
		}
		printf("Invalid command\n");
		return;
	}

	if (img.image_loaded) {
		if (!strchr("25", img.magic_word[1])) {
			printf("Black and white image needed\n");
			return;
		}
	} else {
		printf("No image loaded\n");
		return;
	}

	// Verific daca numarul de bin-uri apartine [2, 256] si este putere a lui 2
	if (bins < 2 || bins > RGB_MAX + 1 || (bins & (bins - 1)) != 0) {
		printf("Invalid set of parameters\n");
		return;
	}

	// Voi avrea nevoie de 256 / bins intervale
	interval_len = (RGB_MAX + 1) / bins;
	make_apparitions(img, ap, interval_len, &max);

	for (int i = 0; i < bins; i++) {
		if (ap[i])
			ap[i] = (int)((double)ap[i] / max * stars);
	}

	for (int i = 0; i < bins; i++) {
		printf("%lld\t|\t", ap[i]);
		for (int j = 1; j <= ap[i]; j++)
			printf("*");
		printf("\n");
	}
}
