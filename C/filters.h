/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#ifndef FILTERS_H
#define FILTERS_H

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

#endif // FILTERS_H
