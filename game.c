#include "game.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

const int32_t base_max_hp = 100;
const int32_t base_damage = 5;
const int32_t bullet_color = 0xFF0000FF;

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
  player->ms = 5;

  player->color = 0xFFFFFFFF;

  player->rect.x = WINDOW_WIDTH / 2;
  player->rect.y = WINDOW_HEIGHT / 2;
  player->rect.h = 25;
  player->rect.w = 25;
}

void init_game(game_t *game) {
  game->state = RUNNING;
  game->keys.w = false;
  game->keys.a = false;
  game->keys.s = false;
  game->keys.d = false;
  game->keys.lc = false;
}

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
  int32_t event_count = 0;
  while (SDL_PollEvent(&event)) {
    event_count++;
    switch (event.type) {
      // handle window close
    case SDL_QUIT:
      game->state = QUIT;
      break;

      // begin keydown case
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        game->state = QUIT;
        break;
      default:
        break;
      }
      break;
      // end keydown case

      // begin mouse down case
    case SDL_MOUSEBUTTONDOWN:
      switch (event.button.button) {
      case (SDL_BUTTON_LEFT):
        game->keys.lc = true;
        game->last_shooting.x = event.button.x;
        game->last_shooting.y = event.button.y;
        break;
      default:
        break;
      }
      break;
      // end mouse down case
      // begin mouse motion case
    case SDL_MOUSEMOTION:
      if (game->keys.lc) {
        game->last_shooting.x = event.motion.x;
        game->last_shooting.y = event.motion.y;
      }
      break;
      // end mouse motion case

      // begin mouse up case
    case SDL_MOUSEBUTTONUP:
      switch (event.button.button) {
      case (SDL_BUTTON_LEFT):
        game->keys.lc = false;
        break;
      default:
        break;
      }
      break;
      // end mouse down case
    default:
      break;
      // end all case
    }
  }
  SDL_PumpEvents();

  const uint8_t *keystate = SDL_GetKeyboardState(NULL);
  game->keys.w = keystate[SDL_SCANCODE_W];
  game->keys.a = keystate[SDL_SCANCODE_A];
  game->keys.s = keystate[SDL_SCANCODE_S];
  game->keys.d = keystate[SDL_SCANCODE_D];
}

void handle_movement(game_t *game, player_t *player) {
  if (game->keys.w && player->rect.y > 0) {
    player->rect.y -= player->ms;
  }
  if (game->keys.a && player->rect.x > 0) {
    player->rect.x -= player->ms;
  }
  if (game->keys.s && player->rect.y + player->rect.h < WINDOW_HEIGHT) {
    player->rect.y += player->ms;
  }
  if (game->keys.d && player->rect.x + player->rect.w < WINDOW_WIDTH) {
    player->rect.x += player->ms;
  }
}

void handle_shooting(game_t *game) {
  if (game->keys.lc) {
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
    handle_movement(&game, &player);
    handle_shooting(&game);
    SDL_Delay(16);
  }

  cleanup();
}
