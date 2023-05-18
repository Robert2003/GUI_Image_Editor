// Copyright Damian Mihai-Robert 312CAb 2022-2023
#pragma once

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "structures.h"

#define ll long long
#define RGB_MAX 255

void make_apparitions(image img, ll ap[], int interval_len, ll * max);
void histogram(image img);
