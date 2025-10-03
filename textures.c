#include "textures.h"

bool load_textures(SDL_Renderer *renderer, textures_t *textures) {
  // load empty heart texture
  SDL_Surface *surf;
  // empty heart
  surf = SDL_LoadBMP("assets/heart_empty.bmp");
  if (!surf) {
    SDL_Log("Unable to load BMP: %s\n", SDL_GetError());
    return false;
  }
  textures->heart_empty = SDL_CreateTextureFromSurface(renderer, surf);
  if (!textures->heart_empty) {
    SDL_Log("Unable to create empty heart texture: %s\n", SDL_GetError());
    return false;
  }

  // full heart
  surf = SDL_LoadBMP("assets/heart_full.bmp");
  if (!surf) {
    SDL_Log("Unable to load BMP: %s\n", SDL_GetError());
    return false;
  }
  textures->heart_full = SDL_CreateTextureFromSurface(renderer, surf);
  if (!textures->heart_full) {
    SDL_Log("Unable to create full heart texture: %s\n", SDL_GetError());
    return false;
  }
  SDL_FreeSurface(surf);
  return true;
}

void free_textures(textures_t *textures) {
  free(textures->heart_empty);
  free(textures->heart_full);
}
