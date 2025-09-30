#pragma once
#include "bullets.h"
#include "common.h"


#include "SDL.h"
#include <stdbool.h>
#include <stdlib.h>

// typedef int names

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  i32 bg_color;
  i32 fg_color;
} sdl_t;

typedef struct {
  bool w;
  bool a;
  bool s;
  bool d;
  bool lc;
} keypad_t;

typedef struct {
  i32 x;
  i32 y;
} point_t;

typedef struct {
  i32 hp;          // health
  i32 max_hp;      // max health
  i32 damage;      // damage per bullet
  i32 color;       // hexadecimal color value
  SDL_Rect rect;   // hitbox
  i32 ms;          // movement speed
  i32 bullet_size; // bullet size
} player_t;

typedef enum {
  RUNNING,
  QUIT,
  PAUSED,
} state_t;

typedef struct {
  state_t state;
  keypad_t keys;
  point_t last_shooting; // this stores the last location of the mouse while the
                         // user is holding down left click
} game_t;

void move_player(game_t *game, player_t *player);
void update_screen(sdl_t *sdl, player_t *player, BulletManager *manager);
bool init_sdl(sdl_t *sdl);
void init_player(player_t *player);
void init_game(game_t *game);
void draw_player(SDL_Renderer *renderer, player_t *player);
void handle_input(game_t *game);
void handle_movement(game_t *game, player_t *player);
void handle_shooting(game_t *game, player_t *player, BulletManager *manager);
