#pragma once
#include "SDL.h"
#include <stdbool.h>
#include <stdint.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WHITE 0xFFFFFFFF
#define BLACK 0x000000FF
#define RED 0xFF0000FF
#define INVULNERABLE 0x88888888

#define BULLET_SPEED 10
typedef int32_t i32;
typedef i32 i8;

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
  bool firing;
} keypad_t;
