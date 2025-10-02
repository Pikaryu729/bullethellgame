#include "game.h"
#include "bullets.h"
#include "math.h"

const i32 base_max_hp = 3;

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
  sdl->bg_color = BLACK;
  // foreground color white
  sdl->fg_color = WHITE;

  return true;
}

void init_player(player_t *player) {
  player->max_hp = base_max_hp;
  player->hp = player->max_hp;
  player->ms = 5;

  player->color = WHITE;

  player->rect.x = WINDOW_WIDTH / 2;
  player->rect.y = WINDOW_HEIGHT / 2;
  player->rect.h = 25;
  player->rect.w = 25;
  player->bullet_size = 5;
}

void init_game(game_t *game) {
  game->state = RUNNING;
  game->keys.w = false;
  game->keys.a = false;
  game->keys.s = false;
  game->keys.d = false;
}

void draw_player(SDL_Renderer *renderer, player_t *player) {
  // extract player color rgb
  i8 color_r = (player->color >> 24) & 0xFF;
  i8 color_g = (player->color >> 16) & 0xFF;
  i8 color_b = (player->color >> 8) & 0xFF;
  i8 color_a = (player->color);

  // set the render color to the color of the player
  SDL_SetRenderDrawColor(renderer, color_r, color_g, color_b, color_a);
  SDL_RenderFillRect(renderer, &player->rect);
}

void update_screen(sdl_t *sdl, player_t *player, BulletManager *manager) {
  // extract bg color rgb
  i8 color_r = (sdl->bg_color >> 24) & 0xFF;
  i8 color_g = (sdl->bg_color >> 16) & 0xFF;
  i8 color_b = (sdl->bg_color >> 8) & 0xFF;
  i8 color_a = (sdl->bg_color);

  SDL_SetRenderDrawColor(sdl->renderer, color_r, color_g, color_b, color_a);
  SDL_RenderClear(sdl->renderer);

  draw_player(sdl->renderer, player);
  draw_bullets(sdl->renderer, manager);
  SDL_RenderPresent(sdl->renderer);
}

void handle_input(game_t *game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
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
    }
  }

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


void cleanup(BulletManager *manager) {
  free_bullet_manager(manager);
  SDL_Quit();
}

int main(void) {

  // initialize sdl subsystems, create window and renderer
  sdl_t sdl;
  if (!init_sdl(&sdl)) {
    SDL_Quit();
    exit(1);
  }

  // set game state to running
  game_t game;
  init_game(&game);

  // set player default values
  player_t player;
  init_player(&player);

  // initialize bullet manager with 10 bullets to start
  BulletManager *manager = create_bullet_manager(10);

  while (game.state != QUIT) {
    handle_input(&game);
    update_screen(&sdl, &player, manager);
    handle_movement(&game, &player);
    update_bullets(manager);
    // ~ 60fps
    SDL_Delay(16);
  }

  cleanup(manager);
}
