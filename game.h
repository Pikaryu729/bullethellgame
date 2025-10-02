#pragma once
#include "bullets.h"
#include "common.h"

#include "SDL.h"
#include <stdbool.h>
#include <stdlib.h>

// typedef int names

typedef struct {
  i32 x;
  i32 y;
} point_t;

typedef struct {
  i32 hp;          // health
  i32 max_hp;      // max health
  i32 color;       // hexadecimal color value
  SDL_Rect rect;   // hitbox
  i32 ms;          // movement speed
  bool recovering; // if player has recently been hit by bullet, they go into
                   // recovery mode, which they cannot be hit
  float recovery_timer; // keeps track of how long the player has been in
                        // recovery mode
  float recovery_dur;   // keeps track of how long the player should be in
                        // recovery mode before going back to normal
} player_t;

typedef enum {
  RUNNING,
  QUIT,
  PAUSED,
} state_t;

typedef struct {
  state_t state;
  keypad_t keys;
  i32 bullet_radius; // bullet radius in pixels
  i32 bullet_speed;  // how many pixels a bullet travels per frame

} game_t;

void move_player(game_t *game, player_t *player);
void update_screen(sdl_t *sdl, player_t *player, BulletManager *manager);
bool init_sdl(sdl_t *sdl);
void init_player(player_t *player);
void init_game(game_t *game);
void draw_player(SDL_Renderer *renderer, player_t *player);
void handle_input(game_t *game);
void handle_movement(game_t *game, player_t *player);
void fire_bullet(BulletManager *manager, game_t *game);
bool check_collision(BulletManager *manager, player_t *player);
void recover(player_t *player);
