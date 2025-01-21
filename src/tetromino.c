#include <math.h>
#include "tetromino.h"


int move_tetromino(Tetromino * tetromino, int amount, Tile * tiles, int tiles_count)
{
	for (int i = 0; i < 4; i++)
	{	

		if (tetromino->active_tiles[i]->x + amount < 0)
		{
			return 1;
		}
		
		if (tetromino->active_tiles[i]->x + amount >= GAME_FIELD_WIDTH)
		{
			return 1;
		}

		

		for(int j = 0; j < tiles_count; j++)
		{

			if (tiles[j].is_active == true)
			{
				continue;
			}

			if (&tiles[j] == tetromino->active_tiles[i])
			{
				continue;
			}

			if (tetromino->active_tiles[i]->x + amount == tiles[j].x)
			{
				if (tetromino->active_tiles[i]->y == tiles[j].y)
				{
					return 1;
				}
			}
		}


	}

	for (int i = 0; i < 4; i++)
	{
		tetromino->active_tiles[i]->x += amount;
	}
	tetromino->x += amount;


	return 0;
}

int move_tetromino_down(Tetromino * tetromino, Tile * tiles, int tiles_count)
{

	for (int i = 0; i < 4; i++)
	{
		
		if (tetromino->active_tiles[i]->y + TILESIZE >= DISPLAY_HEIGHT)
		{
			return 1;
		}


		for(int j = 0; j < tiles_count; j++)
		{
			if (tiles[j].is_active == true)
			{
				continue;
			}


			if (&tiles[j] == tetromino->active_tiles[i])
			{
				continue;
			}

			if (tetromino->active_tiles[i]->y + TILESIZE == tiles[j].y)
			{
				if (tetromino->active_tiles[i]->x == tiles[j].x)
				{
					return 1;
				}
			}

		}
	}

	for (int i = 0; i < 4; i++)
	{
		tetromino->active_tiles[i]->y += TILESIZE;
	}
	tetromino->y += TILESIZE;

	return 0;
}

int rotate_tetromino(Tetromino * tetromino, Tile * tiles, int tiles_count)
{

	if (tetromino->type == TETROMINO_O)
	{
		return 0;
	}
	

	int center_x;
	int center_y;

	center_x = tetromino->x + TILESIZE;
	center_y = tetromino->y + TILESIZE;


	if (tetromino->type == TETROMINO_I)
	{
		center_x = tetromino->x + TILESIZE + TILESIZE / 2;
		center_y = tetromino->y + TILESIZE + TILESIZE / 2;
	}

	int prev_x[4];
	int prev_y[4];

	for (int i = 0; i < 4; i++)
	{
		prev_x[i] = tetromino->active_tiles[i]->x;
		prev_y[i] = tetromino->active_tiles[i]->y;
	}

	for (int i = 0; i < 4; i ++)
	{

		int relative_x = tetromino->active_tiles[i]->x - center_x;
		int relative_y = tetromino->active_tiles[i]->y - center_y;
		
		// (x′,y′)=(y,−x)
		int new_x = -relative_y;
		int new_y =  relative_x;

		relative_x = new_x;
		relative_y = new_y;


		//recenter correction
		relative_x = relative_x + center_x;
		relative_y = relative_y + center_y;

		tetromino->active_tiles[i]->x = relative_x;
		tetromino->active_tiles[i]->y = relative_y;

		if (tetromino->active_tiles[i]->y >= DISPLAY_HEIGHT)
		{
			goto rotation_clear_rotatation_label;
		}

		if (tetromino->active_tiles[i]->x < 0)
		{
			goto rotation_clear_rotatation_label;
		}
		
		if (tetromino->active_tiles[i]->x >= GAME_FIELD_WIDTH)
		{
			goto rotation_clear_rotatation_label;
		}

		for(int j = 0; j < tiles_count; j++)
		{
			if (tiles[j].is_active == true)
			{
				continue;
			}


			if (&tiles[j] == tetromino->active_tiles[i])
			{
				continue;
			}

			if (tetromino->active_tiles[i]->y == tiles[j].y)
			{
				if (tetromino->active_tiles[i]->x == tiles[j].x)
				{
					goto rotation_clear_rotatation_label;
				}
			}

		}

	}

	goto rotation_end_label;

rotation_clear_rotatation_label:
	
	for (int i = 0; i < 4; i++)
	{
		tetromino->active_tiles[i]->x = prev_x[i];
		tetromino->active_tiles[i]->y = prev_y[i];
	}
	
	return 1;


rotation_end_label:

	return 0;
}


int set_tetromino(Tetromino * tetromino, Tile * tiles, int tiles_count, TetrominoTypes type)
{


	int coordinates[4][2];
	get_tetrominos(type, coordinates);

	int type_int = (int)type;

	for (int i = 0; i < 4; i++)
	{
		tiles_count = add_tile(coordinates[i][0] * TILESIZE + 3 * TILESIZE, coordinates[i][1] * TILESIZE, tiles, tiles_count, type_int);
		tetromino->active_tiles[i] = &tiles[tiles_count - 1];
	}

	tetromino->type = type;

	tetromino->x = 3 * TILESIZE;
	tetromino->y = 0;

	return tiles_count;
}

void get_tetrominos(TetrominoTypes type, int coordinates[4][2]) {
	switch (type)
	{
		case TETROMINO_I:

			coordinates[0][0] = 0; coordinates[0][1] = 1;
			coordinates[1][0] = 1; coordinates[1][1] = 1;
			coordinates[2][0] = 2; coordinates[2][1] = 1;
			coordinates[3][0] = 3; coordinates[3][1] = 1;
			break;

		case TETROMINO_J:

			coordinates[0][0] = 0; coordinates[0][1] = 1;
			coordinates[1][0] = 1; coordinates[1][1] = 1;
			coordinates[2][0] = 2; coordinates[2][1] = 1;
			coordinates[3][0] = 2; coordinates[3][1] = 2;
			break;

		case TETROMINO_L:

			coordinates[0][0] = 0; coordinates[0][1] = 1;
			coordinates[1][0] = 0; coordinates[1][1] = 2;
			coordinates[2][0] = 1; coordinates[2][1] = 1;
			coordinates[3][0] = 2; coordinates[3][1] = 1;
			break;

		case TETROMINO_O:

			coordinates[0][0] = 0; coordinates[0][1] = 0;
			coordinates[1][0] = 0; coordinates[1][1] = 1;
			coordinates[2][0] = 1; coordinates[2][1] = 0;
			coordinates[3][0] = 1; coordinates[3][1] = 1;
			break;

		case TETROMINO_S:

			coordinates[0][0] = 0; coordinates[0][1] = 2;
			coordinates[1][0] = 1; coordinates[1][1] = 1;
			coordinates[2][0] = 1; coordinates[2][1] = 2;
			coordinates[3][0] = 2; coordinates[3][1] = 1;
			break;

		case TETROMINO_T:

			coordinates[0][0] = 0; coordinates[0][1] = 1;
			coordinates[1][0] = 1; coordinates[1][1] = 1;
			coordinates[2][0] = 1; coordinates[2][1] = 2;
			coordinates[3][0] = 2; coordinates[3][1] = 1;
			break;

		case TETROMINO_Z:

			coordinates[0][0] = 0; coordinates[0][1] = 1;
			coordinates[1][0] = 1; coordinates[1][1] = 1;
			coordinates[2][0] = 1; coordinates[2][1] = 2;
			coordinates[3][0] = 2; coordinates[3][1] = 2;
			break;
		
	}
}



int update_tetromino(Tetromino * tetromino, Tile * tiles, int tiles_count)
{
	if (move_tetromino_down(tetromino, tiles, tiles_count) == 1)
	{
		if (tetromino->y == 0)
		{
			return -1;
		}
		//we could not move and have to now create a new tetromino
		for (int i = 0; i < 4; i++)
		{
			tetromino->active_tiles[i]->is_active = false;
		}
		return 1;

	} 

	return 0;
}