// Copyright Damian Mihai-Robert 312CAb 2022-2023
#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "structures.h"

void rotate(image * img, coordinates * selection);

void rotate_180(image *img, coordinates selection, int angle,
				bool print);

void rotate_90_counter_clockwise(image *img, coordinates *selection, int angle);

void rotate_90_clockwise(image *img, coordinates *selection, int angle);

