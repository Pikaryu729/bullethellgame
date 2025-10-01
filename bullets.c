#include "bullets.h"

const i32 bullet_color = RED;

BulletManager *create_bullet_manager(i32 initial_capacity) {
  BulletManager *manager = malloc(sizeof(BulletManager));
  manager->bullets = malloc(sizeof(bullet_t) * initial_capacity);
  manager->count = 0;
  manager->capacity = initial_capacity;
  return manager;
}

void add_bullet(BulletManager *manager, SDL_Rect rect, i32 vx, i32 vy) {
  if (manager->count >= manager->capacity) {
    manager->capacity *= 2;
    manager->bullets =
        realloc(manager->bullets, manager->capacity * sizeof(bullet_t));
  }
  manager->bullets[manager->count].rect = rect;
  manager->bullets[manager->count].vx = vx;
  manager->bullets[manager->count].vy = vy;

  ++manager->count;
}

void update_bullets(BulletManager *manager) {
  for (i32 i = 0; i < manager->count; i++) {
    manager->bullets[i].rect.x += manager->bullets[i].vx;
    manager->bullets[i].rect.y += manager->bullets[i].vy;

    if (is_bullet_offscreen(&manager->bullets[i])) {
      manager->bullets[i] = manager->bullets[manager->count - 1];
      --manager->count;
    }
  }
}

bool is_bullet_offscreen(bullet_t *bullet) {
  if (bullet->rect.x > WINDOW_WIDTH || bullet->rect.x < 0) {
    return true;
  }
  if (bullet->rect.y > WINDOW_HEIGHT || bullet->rect.y < 0) {
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
    SDL_Rect *bullet_rect = &manager->bullets[i].rect;
    SDL_RenderFillRect(renderer, bullet_rect);
  }
}

void free_bullet_manager(BulletManager *manager) {
  free(manager->bullets);
  free(manager);
}
