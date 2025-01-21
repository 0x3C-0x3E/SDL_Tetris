#pragma once
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

#include "globals.h"
#include "drawing_context.h"
#include "renderer.h"

typedef struct Tile
{
	int x;
	int y;

	bool is_active;

	SDL_Rect image_rect;

} Tile;

int add_tile(int x, int y, Tile * tiles, int tiles_count, int type);

void render_tile(Tile * tile);

void remove_tile(int index, Tile * tiles, int tiles_count);
