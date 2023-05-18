// Copyright Damian Mihai-Robert 312CAb 2022-2023
#pragma once

// Definirea unui pixel RGB
typedef struct {
	int r, g, b;
} rgb_pixel;

// Definirea union-ului care poate fi ori pixel de tip rgb, ori grayscale
typedef union {
	rgb_pixel rgb;
	int grayscale;
} pixel;

// Definirea unei imagini
typedef struct {
	bool image_loaded;
	char magic_word[3];
	int width;
	int height;
	int maxval;
	pixel **data;
} image;

// Definirea unui punct cartezian
typedef struct {
	int x, y;
} point;

// Definirea structului pentru selectie
typedef struct {
	point top_left;
	int width;
	int height;
} coordinates;
