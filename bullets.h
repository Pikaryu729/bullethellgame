#pragma once
#include "SDL.h"
#include "common.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  i32 damage;
  SDL_Rect rect;
  i32 vx;
  i32 vy;
} bullet_t;

typedef struct {
  bullet_t *bullets;
  i32 count;
  i32 capacity;
} BulletManager;

BulletManager *create_bullet_manager(i32 initial_capacity);

void add_bullet(BulletManager *manager, SDL_Rect rect, i32 vx, i32 vy);
void update_bullets(BulletManager *manager);
void free_bullet_manager(BulletManager *manager);
bool is_bullet_offscreen(bullet_t *bullet);
void draw_bullets(SDL_Renderer *renderer, BulletManager *manager);
