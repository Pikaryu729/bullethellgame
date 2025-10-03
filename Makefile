CFLAGS = -std=c17 -Wall -Wextra -Werror

all:
	gcc textures.c game.c bullets.c -o game $(CFLAGS) `sdl2-config --cflags --libs` -lm

debug:
	gcc -g textures.c game.c bullets.c -o game $(CFLAGS) `sdl2-config --cflags --libs` -lm -DDEBUG
