/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#ifndef SELECTION_H
#define SELECTION_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "structures.h"

#define LENGTH 20

void swap(void *a, void *b, size_t size);
void select_all(image img, coordinates *selection, bool new_image);
void select_region(image img, coordinates *selection);

#endif // SELECTION_H
