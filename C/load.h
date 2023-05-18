// Copyright Damian Mihai-Robert 312CAb 2022-2023
#pragma once

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "structures.h"

#define LINE_LEN 100

void load_utility(FILE * *f, char command[], char filename[], image * img,
				  coordinates * selection);
