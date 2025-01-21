#include "tile.h"



int add_tile(int x, int y, Tile * tiles, int tiles_count, int type)
{
	tiles[tiles_count] = {
		.x = x,
		.y = y,
		.is_active = true,
		.image_rect = {0, type * TILESIZE, TILESIZE, TILESIZE}
	};
	tiles_count += 1;
	return tiles_count;
}


void render_tile(Tile * tile)
{
	render(drawing_context.tileset, tile->image_rect, tile->x, tile->y);
}

void remove_tile(int index, Tile * tiles, int tiles_count)
{
	for (int i = index; i < tiles_count - 1; i++)
	{
		tiles[i] = tiles[i + 1];
	}
}