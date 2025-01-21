#pragma once
#include "globals.h"
#include "tile.h"

typedef enum {
	TETROMINO_I,
    TETROMINO_J,
    TETROMINO_L,
    TETROMINO_O,
    TETROMINO_S,
    TETROMINO_T,
    TETROMINO_Z

} TetrominoTypes;

typedef struct
{
	Tile * active_tiles[4];

	int x;
	int y;

	TetrominoTypes type;


} Tetromino;


int move_tetromino(Tetromino * tetromino, int amount, Tile * tiles, int tiles_count);

int move_tetromino_down(Tetromino * tetromino, Tile * tiles, int tiles_count);

int rotate_tetromino(Tetromino * tetromino, Tile * tiles, int tiles_count);


int set_tetromino(Tetromino * tetromino, Tile * tiles, int tiles_count, TetrominoTypes type);

void get_tetrominos(TetrominoTypes type, int coordinates[4][2]);

int update_tetromino(Tetromino * tetromino, Tile * tiles, int tiles_count);