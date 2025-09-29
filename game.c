#include "SDL.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

const int32_t base_max_hp = 100;
const int32_t base_damage = 5;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} sdl_t;

typedef struct {
  int32_t x;
  int32_t y;
} pos_t;

typedef struct {
  int32_t hp;
  int32_t max_hp;
  int32_t damage;
  pos_t pos;
} player_t;

typedef enum {
  RUNNING,
  QUIT,
  PAUSED,
} state_t;

typedef struct {
  state_t state;
} game_t;

bool init_sdl(sdl_t *sdl) {
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
    SDL_Log("Error initializing sdl: %s \n", SDL_GetError());
  }
  sdl->window = SDL_CreateWindow("Survivor Game", SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
  if (!sdl->window) {
    SDL_Log("Error creating window: %s \n", SDL_GetError());
    return false;
  }

  sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0);
  if (!sdl->renderer) {
    SDL_Log("Error creating renderer: %s \n", SDL_GetError());
    return false;
  }
  return true;
}

void init_player(player_t *player) {
  player->max_hp = base_max_hp;
  player->hp = player->max_hp;
  player->damage = base_damage;
  player->pos.x = WINDOW_WIDTH/ 2;
  player->pos.y = WINDOW_HEIGHT / 2;
}

void draw_player(player_t *player) {

}

void cleanup() { SDL_Quit(); }

int main(void) {

  sdl_t sdl;
  if (!init_sdl(&sdl)) {
    cleanup();
    exit(1);
  }

  player_t player;
  init_player(&player);

  cleanup();
}
