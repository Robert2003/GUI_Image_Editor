/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#include "load.h"
#include "memory_manipulation.h"
#include "selection.h"

/*
Functie care ignora comentariile si spatiile din imagini
*/
void ignore_comments(FILE *f)
{
	int ch;
	char line[LINE_LEN];

	// Ignora toate spatiile
	while ((ch = fgetc(f)) != EOF && isspace(ch))
		;

	// Daca e comentariu, citeste toata linia
	if (ch == '#') {
		fgets(line, sizeof(line), f);
		ignore_comments(f);
	/*
	Daca nu e comentariu, citirea de caractere a citit si un caracter care face
	parte din datele imaginii, asa ca trebuie sa ne intoarcem un caracter in
	spate
	*/
	} else {
		fseek(f, -1, SEEK_CUR);
	}
}

/*
Functie care deschide un fisier si verifica daca este binar sau ascii
*/
bool open_file(FILE **f, char filename[])
{
	(*f) = fopen(filename, "rt");
	if (!*f)
		return false;
	char magic_word[3];
	fscanf((*f), "%s", magic_word);
	// Daca este binar, inchide fisierul si il deschide sub format binar
	if (magic_word[1] == '5' || magic_word[1] == '6') {
		fclose((*f));
		(*f) = fopen(filename, "rb");
		return true;
	}
	// Daca este ascii muta cursorul la inceputul fisierului
	fseek((*f), 0, SEEK_SET);
	return true;
}

/*
Functie care citeste magic word-ul, latimea, inaltimea si valoarea maxima
a unui pixel
*/
void read_metadatas(FILE *f, image *img, char magic_word[])
{
	strcpy(img->magic_word, magic_word);
	fscanf(f, "%d", &img->width);
	ignore_comments(f);
	fscanf(f, "%d", &img->height);
	ignore_comments(f);
	fscanf(f, "%d", &img->maxval);
	ignore_comments(f);
}

/*
Functie care citeste matricea de pixeli a unei imagini si returneaza true daca
citirea se poate realiza, sau false atfel
*/
bool read_data(FILE *f, image *img, char magic_word[])
{
	int width, height;
	unsigned char r, g, b, grayscale;
	width = img->width;
	height = img->height;

	// Creeaza o matrice auxiliara ascii, pentru programarea defensiva
	pixel **aux = NULL;
	aux = alloc_matrix(width, height);

	// Daca nu s-a alocat memorie, returnam false
	if (!aux)
		return false;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// Daca magic wordul este P3 sau P6, este poza RGB
			if (magic_word[1] <= '3') {
				if (img->magic_word[1] == '3') {
					fscanf(f, "%d", &aux[i][j].rgb.r);
					fscanf(f, "%d", &aux[i][j].rgb.g);
					fscanf(f, "%d", &aux[i][j].rgb.b);
				// Daca magic wordul este P2 sau P5, este poza grayscale
				} else {
					fscanf(f, "%d", &aux[i][j].grayscale);
				}
			} else {
				if (img->magic_word[1] == '6') {
					fscanf(f, "%c%c%c", &r, &g, &b);
					aux[i][j].rgb.r = (int)r;
					aux[i][j].rgb.g = (int)g;
					aux[i][j].rgb.b = (int)b;
				// Daca magic wordul este P2 sau P5, este poza grayscale
				} else {
					fscanf(f, "%c", &grayscale);
					aux[i][j].grayscale = grayscale;
				}
			}
		}
	}
	// Variabila care stocheaza matricea primeste pointer la auxiliara
	img->data = aux;
	// Citirea imaginii a avut succes
	return true;
}

/*
Functie care incarca o imagine in memorie
*/
bool load(FILE **f, image *img, char filename[])
{
	bool success = true;
	// Daca o poza este deja incarcata in memorie, o sterg
	if (img->image_loaded)
		remove_photo(img);
	// Deschid fisierul de citire
	img->image_loaded = open_file(f, filename);

	if (!(*f) || !img->image_loaded) {
		printf("Failed to load %s\n", filename);
		return false;
	}
	// Citesc magic word-ul
	char magic_word[3];
	ignore_comments((*f));
	fscanf((*f), "%s", magic_word);
	ignore_comments((*f));
	// Citesc metadatele imaginii (width, height, max_val)
	read_metadatas((*f), img, magic_word);
	// Citesc imaginea si verific daca incarcarea a avut succes
	if (!read_data((*f), img, magic_word))
		success = false;
	if (!success) {
		printf("Failed to load %s\n", filename);
		fclose((*f));
		return false;
	}
	printf("Loaded %s\n", filename);
	fclose((*f));
	return true;
}

/*
Functie ajutatoare care realizeaza citirea parametrilor comenzii LOAD, si
apeleaza functiile de incarcare a imaginii in memorie
*/
void  load_utility(FILE **f, char command[], char filename[], image *img,
				   coordinates *selection)
{
	if (!strcmp(command, "LOAD")) {
		load(f, img, filename);
		// Cand o noua poza este incarcata, aceasta este selectata in intregime
		if (img->image_loaded)
			select_all(*img, selection, true);
	}
}
