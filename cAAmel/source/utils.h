#pragma once

#ifndef UTILS_H
#define UTILS_H

#include "../include/cJSON.h"

#include <SDL2/SDL.h>

cJSON* cJSON_from_file(char* file_path);
int check_sdl_code(int code);
void* check_sdl_ptr(void* ptr);
void load_localisation(char *out, const char *name, const cJSON *translation);

int maxi(int a, int b);

#endif
