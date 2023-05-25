/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#ifndef MEMORY_MANIPULATION_H
#define MEMORY_MANIPULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structures.h"

void free_matrix(pixel * *mat, int n);
void remove_photo(image *img);
pixel **alloc_matrix(int width, int height);

#endif // MEMORY_MANIPULATION_H
