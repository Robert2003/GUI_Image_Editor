/* Copyright 2023 <Ⓒ Andrei Pirlea and Robert-Mihai Damian - 312CA 2022-2023>*/
#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "structures.h"

#define LENGTH 20

#define UC unsigned char

void save_image(image img, char *file_name, char type);

#endif // SAVE_H
