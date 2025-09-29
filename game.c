#include "SDL.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

const int32_t base_max_hp = 100;
const int32_t base_damage = 5;
const int32_t bullet_color = 0xFF0000FF;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int32_t bg_color;
  int32_t fg_color;
} sdl_t;

typedef struct {
  int32_t x;
  int32_t y;
} pos_t;

typedef struct {
  int32_t hp;
  int32_t max_hp;
  int32_t damage;
  int32_t color;
  SDL_Rect rect;
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

  // initialize background to black
  sdl->bg_color = 0x000000FF;
  // foreground color white
  sdl->fg_color = 0xFFFFFFFF;

  return true;
}

void init_player(player_t *player) {
  player->max_hp = base_max_hp;
  player->hp = player->max_hp;
  player->damage = base_damage;

  player->color = 0xFFFFFFFF;

  player->rect.x = WINDOW_WIDTH / 2;
  player->rect.y = WINDOW_HEIGHT / 2;
  player->rect.h = 25;
  player->rect.w = 25;
}

void init_game(game_t *game) { game->state = RUNNING; }

void draw_player(sdl_t *sdl, player_t *player) {
  // extract player color rgb
  int8_t color_r = (player->color >> 24) & 0xFF;
  int8_t color_g = (player->color >> 16) & 0xFF;
  int8_t color_b = (player->color >> 8) & 0xFF;
  int8_t color_a = (player->color);

  // set the render color to the color of the player
  SDL_SetRenderDrawColor(sdl->renderer, color_r, color_g, color_b, color_a);
  SDL_RenderFillRect(sdl->renderer, &player->rect);
}

void update_screen(sdl_t *sdl, player_t *player) {
  // extract bg color rgb
  int8_t color_r = (sdl->bg_color >> 24) & 0xFF;
  int8_t color_g = (sdl->bg_color >> 16) & 0xFF;
  int8_t color_b = (sdl->bg_color >> 8) & 0xFF;
  int8_t color_a = (sdl->bg_color);

  SDL_SetRenderDrawColor(sdl->renderer, color_r, color_g, color_b, color_a);
  SDL_RenderClear(sdl->renderer);

  draw_player(sdl, player);

  SDL_RenderPresent(sdl->renderer);
}

void handle_input(game_t *game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      game->state = QUIT;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        game->state = QUIT;
        break;
      }
    }
  }
}
void cleanup(void) { SDL_Quit(); }

int main(void) {

  // initialize sdl subsystems, create window and renderer
  sdl_t sdl;
  if (!init_sdl(&sdl)) {
    cleanup();
    exit(1);
  }
  // set game state to running
  game_t game;
  init_game(&game);

  // set player default values
  player_t player;
  init_player(&player);

  while (game.state != QUIT) {
    handle_input(&game);
    update_screen(&sdl, &player);
  }

  cleanup();
}
