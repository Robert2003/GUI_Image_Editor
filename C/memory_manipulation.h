// Copyright Damian Mihai-Robert 312CAb 2022-2023
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structures.h"

void free_matrix(pixel * *mat, int n);
void remove_photo(image *img);
pixel **alloc_matrix(int width, int height);
