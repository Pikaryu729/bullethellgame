#pragma once

#include "SDL.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  int32_t damage;
  SDL_Rect rect;
  int32_t vx;
  int32_t vy;
} bullet_t;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int32_t bg_color;
  int32_t fg_color;
} sdl_t;

typedef struct {
  bool w;
  bool a;
  bool s;
  bool d;
  bool lc;
} keypad_t;

typedef struct {
  int32_t x;
  int32_t y;
} point_t;

typedef struct {
  int32_t hp;     // health
  int32_t max_hp; // max health
  int32_t damage; // damage per bullet
  int32_t color;  // hexadecimal color value
  SDL_Rect rect;  // hitbox
  int32_t ms;     // movement speed
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
