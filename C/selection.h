// Copyright Damian Mihai-Robert 312CAb 2022-2023
#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "structures.h"

#define LENGTH 20

void swap(void *a, void *b, size_t size);
void select_all(image img, coordinates *selection, bool new_image);
void select_region(image img, coordinates *selection);
