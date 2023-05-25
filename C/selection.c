/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#include "selection.h"

// Functia swap care inverseaza 2 variabile, indiferent de tipul de data
void swap(void *a, void *b, size_t size)
{
	unsigned char aux[size];

	memcpy(aux, a, size);
	memcpy(a, b, size);
	memcpy(b, aux, size);
}

// Functia care ordoneaza x1 si x2, respectiv y1 si y2
void order(int *x1, int *y1, int *x2, int *y2)
{
	if (*x1 > *x2)
		swap(x1, x2, sizeof(*x1));
	if (*y1 > *y2)
		swap(y1, y2, sizeof(*y1));
}

// Functia care verifica daca selectia este in interiorul imaginii
bool check_in_bounds(image img, int x1, int y1, int x2, int y2)
{
	int width, height;
	width = img.width;
	height = img.height;

	if (x1 < 0 || x2 > width || x1 == x2)
		return 0;
	if (y1 < 0 || y2 > height || y1 == y2)
		return 0;
	return 1;
}

// Functia care aduce selectia la imaginea intreaga
void select_all(image img, coordinates *selection, bool new_image)
{
	if (!img.image_loaded && !new_image) {
		printf("No image loaded\n");
	} else {
		selection->top_left.x = 0;
		selection->top_left.y = 0;

		selection->width = img.width;
		selection->height = img.height;

		/*
		Folosesc aceeasi functie si pentru a selecta intreaga imagine cand una
		noua este incarcata, deci nu trebuie sa printez mereu mesajul
		*/
		if (!new_image)
			printf("Selected ALL\n");
	}
}

// Functia care modifica selectia la o zona delimitata de [x1, x2) si [y1, y2)
void change_coordinates(image img, coordinates *selection, int x1, int y1,
						int x2, int y2)
{
	order(&x1, &y1, &x2, &y2);
	if (!img.image_loaded) {
		printf("No image loaded\n");
	} else if (check_in_bounds(img, x1, y1, x2, y2)) {
		selection->top_left.x = y1;
		selection->top_left.y = x1;

		selection->width = x2 - x1;
		selection->height = y2 - y1;

		printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
	} else {
		printf("Invalid set of coordinates\n");
	}
}

// Functia care converteste un string in int (nu stiam de atoi cand am facut-o)
int string_to_int(char s[])
{
	int i = 0, nr = 0;
	while (s[i] != '\0') {
		nr = nr * 10 + (s[i] - '0');
		i++;
	}
	return nr;
}

// Functie care citeste un sir de caractere si il converteste in numar
bool read_number(int *x, bool should_check)
{
	int start_pos = 0, multiply = 1;
	char buff[LENGTH], ch;
	scanf("%s%c", buff, &ch);

	/*
	Primele 3 numere din comanda SELECT sunt urmate de spatiu.
	should_check este 1 pentru primele 3 numere, deoarece la ultimul nu trebuie
	sa verifice daca este urmat de spatiu
	*/
	if (ch != ' ' && should_check)
		return 0;
	// Daca primul caracter este -, poate este un numar negativ
	if (buff[0] == '-') {
		start_pos = 1;
		multiply = -1;
	}
	// Verific sa am doar cifre, ca sa fie numar
	for (size_t i = start_pos; i < strlen(buff); i++)
		if (!(buff[i] >= '0' && buff[i] <= '9'))
			return 0;
	*x = multiply * string_to_int(buff);
	return 1;
}

// Functia care realizeaza comanda SELECT
void select_region(image img, coordinates *selection)
{
	char buff[LENGTH], ch;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	bool valid = true;

	scanf("%s", buff);
	// Daca trebuie selectata intreaga imagine
	if (!strcmp(buff, "ALL")) {
		select_all(img, selection, false);
	} else {
		// Citesc 4 stringuri pe care le convertesc in numere, daca e posibil
		scanf("%c", &ch);
		if (ch != ' ') {
			printf("Invalid command\n");
			return;
		}

		x1 = string_to_int(buff);
		valid = read_number(&y1, true);
		if (!valid) {
			printf("Invalid command\n");
			return;
		}
		valid = read_number(&x2, true);
		if (!valid) {
			printf("Invalid command\n");
			return;
		}
		valid = read_number(&y2, false);
		if (!valid) {
			printf("Invalid command\n");
			return;
		}
		change_coordinates(img, selection, x1, y1, x2, y2);
	}
}
