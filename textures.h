#pragma once
#include "common.h"

typedef struct {
  SDL_Texture *heart_full;
  SDL_Texture *heart_empty;
} textures_t;

bool load_textures(SDL_Renderer *renderer, textures_t *textures);
void free_textures(textures_t *textures);
