CFLAGS = -std=c17 -Wall -Wextra -Werror

all:
	gcc game.c -o game $(CFLAGS) `sdl2-config --cflags --libs`
