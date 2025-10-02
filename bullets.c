#include "bullets.h"

const i32 bullet_color = RED;

BulletManager *create_bullet_manager(i32 initial_capacity) {
  BulletManager *manager = malloc(sizeof(BulletManager));
  manager->bullets = malloc(sizeof(bullet_t) * initial_capacity);
  manager->count = 0;
  manager->capacity = initial_capacity;
  return manager;
}

void add_bullet(BulletManager *manager, i32 x, i32 y, i32 vx, i32 vy,
                i32 radius) {
  if (manager->count >= manager->capacity) {
    manager->capacity *= 2;
    manager->bullets =
        realloc(manager->bullets, manager->capacity * sizeof(bullet_t));
  }
  manager->bullets[manager->count].x = x;
  manager->bullets[manager->count].y = y;
  manager->bullets[manager->count].vx = vx;
  manager->bullets[manager->count].vy = vy;
  manager->bullets[manager->count].radius = radius;

  ++manager->count;
}

void update_bullets(BulletManager *manager) {
  for (i32 i = 0; i < manager->count; i++) {
    manager->bullets[i].x += manager->bullets[i].vx;
    manager->bullets[i].y += manager->bullets[i].vy;

    if (is_bullet_offscreen(&manager->bullets[i])) {
      manager->bullets[i] = manager->bullets[manager->count - 1];
      --manager->count;
    }
  }
}

bool is_bullet_offscreen(bullet_t *bullet) {
  if (bullet->x > WINDOW_WIDTH || bullet->x < 0) {
    return true;
  }
  if (bullet->y > WINDOW_HEIGHT || bullet->y < 0) {
    return true;
  }
  return false;
}

// sets bullet render color to bullet color and then draws it to screen
void draw_bullets(SDL_Renderer *renderer, BulletManager *manager) {
  i8 r = (RED >> 24) & 0xFF;
  i8 g = (RED >> 16) & 0xFF;
  i8 b = (RED >> 8) & 0xFF;
  i8 a = (RED);
  SDL_SetRenderDrawColor(renderer, r, g, b, a);

  for (i32 i = 0; i < manager->count; i++) {
    draw_bullet(renderer, &manager->bullets[i]);
  }
}

void draw_bullet(SDL_Renderer *renderer, bullet_t *bullet) {
  i32 radius = bullet->radius;
  for (int y = -radius; y <= radius; y++) {
    for (int x = -radius; x <= radius; x++) {
      if (x * x + y * y <= radius * radius) {
        SDL_RenderDrawPoint(renderer, bullet->x + x, bullet->y + y);
      }
    }
  }
}

void free_bullet_manager(BulletManager *manager) {
  free(manager->bullets);
  free(manager);
}
