// Copyright Damian Mihai-Robert 312CAb 2022-2023
#pragma once

#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "structures.h"

#define LENGTH 20
#define MIN 0
#define MAX 255

void apply(image *img, coordinates selection, char *filter_name);
