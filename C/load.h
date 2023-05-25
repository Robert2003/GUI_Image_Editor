/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "structures.h"

#define LINE_LEN 100

void load_utility(FILE * *f, char command[], char filename[], image * img,
				  coordinates * selection);

#endif // LOAD_H
