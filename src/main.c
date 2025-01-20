#include "main.h"
#include <math.h>

Drawing_Context drawing_context;


float hireTimeInSeconds()
{
	float t = SDL_GetTicks();
	t *= 0.001f;

	return t;
}

int init_sdl()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	if (!IMG_Init(IMG_INIT_PNG)) {
		printf("SDL_Image could not initialize!\n");
		return 1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
		return 1;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}
	
	sdl_window = SDL_CreateWindow(
		"Tetris",
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		SDL_WINDOW_SHOWN
		);
	sdl_renderer = SDL_CreateRenderer(
		sdl_window,
		-1,
		SDL_RENDERER_ACCELERATED
		);

	SDL_SetRenderDrawColor(sdl_renderer, 50, 50, 50, 255);

	return 0;
}

void init_drawing_context()
{
	drawing_context = {
		sdl_renderer,
		load_texture("data/tileset.png", sdl_renderer)
	};
}


void check_for_lines_cleared()
{
	int found_lines = 0;
	for (int y = 0; y < 20; y++)
	{
		int found_tiles = 0;
		for (int i = 0; i < tiles_count; i++)
		{
			if (tiles[i].y == y * TILESIZE)
			{
				found_tiles ++;
			}
		}

		if (found_tiles == 10)
		{
			clear_line(y);
			found_lines ++;
		}
	}

	switch(found_lines)
	{
	case 0:
		break;

	case 1:
		score += 100;
		break;

	case 2:
		score += 300;
		break;

	case 3:
		score += 600;
		break;

	case 4:
		score += 1000;
		break;	
		
	}

}

void clear_line(int y)
{
	lines_cleared ++;


	int last_checked_index = 0;
	for (int tile = 0; tile < 10; tile ++)
	{

		for (int i = last_checked_index; i < tiles_count; i++)
		{
			if (tiles[i].y == y * TILESIZE)
			{
				last_checked_index = i;
				break;
			}
		}

		for (int j = last_checked_index; j < tiles_count - 1; j++)
		{
			tiles[j] = tiles[j + 1];
		}
		tiles_count --;
	}

	
	for (int i = 0; i < tiles_count; i++)
	{
		if( tiles[i].y < y * TILESIZE)
		{
			tiles[i].y += TILESIZE;
		}
	}
	
}

int run()
{
	srand(time(NULL));

	int quit = 0;

	SDL_Event e;

	while (!quit)
	{

		int startTicks = SDL_GetTicks();
		float newTime = hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		deltaTime = frameTime;

		currentTime = newTime;
		accumulator += frameTime;

		globalTime += 1.0;

		while (accumulator >= timeStep) {

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = 1;
					return 0;
				}

				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.scancode)
					{
					case SDL_SCANCODE_UP:
						rotate_tetromino(&active_tetromino, tiles, tiles_count);
						break;
					case SDL_SCANCODE_LEFT:
						move_tetromino(&active_tetromino, -TILESIZE, tiles, tiles_count);
						break;

					case SDL_SCANCODE_RIGHT:
						move_tetromino(&active_tetromino, TILESIZE, tiles, tiles_count);
						break;
					case SDL_SCANCODE_DOWN:

						if (TICK_RATE != 15)
						{
							tick_accumilator = 0;
						}
						TICK_RATE = 15;
						max_tick_accumilator = REFRESH_RATE / TICK_RATE;
						break;

					case SDL_SCANCODE_RETURN:

						gameover = false;
						
						return 1;


					default:
						break;
					}
				}
				if (e.type == SDL_KEYUP)
				{
					if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
					{
						if (TICK_RATE != 2)
						{
							tick_accumilator = 0;
						}
						TICK_RATE = 2;
						max_tick_accumilator = REFRESH_RATE / TICK_RATE;
						tick_accumilator = 0;
					}
				}
			}

			accumulator -= timeStep;
		}

		all_time ++;

		// ## Update ##

		tick_accumilator ++;
		if (tick_accumilator >= max_tick_accumilator && !(gameover))
		{
			tick_accumilator = 0;


			
			int result = update_tetromino(&active_tetromino, tiles, tiles_count);

			if (result== 1)
			{
				check_for_lines_cleared();
				set_tetromino(&active_tetromino, tiles, tiles_count, next_tetromino);
				next_tetromino = (TetrominoTypes) (rand() % 7);
				tiles_count += 4;

			}

			if (result == -1)
			{
				//game over
				gameover = true;
			}

		}



		// ## Draw ##

		render_clear();

		for (int i = 0; i < tiles_count; i++)
		{
			render_tile(&tiles[i]);
		}


		SDL_SetRenderDrawColor(sdl_renderer, 25, 25, 25, 255);
		SDL_Rect rect = {400, 0, 200, SCREEN_HEIGHT};
		SDL_RenderFillRect(drawing_context.renderer, &rect);
		SDL_SetRenderDrawColor(sdl_renderer, 50, 50, 50, 255);



		render_text("Tetris!", font, (SDL_Color) {255, 255, 255}, 500, 100, centered);


		char buffer[256];
 
		sprintf(buffer, "%d", score);

		render_text("Score:", font, (SDL_Color) {255, 255, 255}, 500, 200, centered);
		render_text(buffer, font, (SDL_Color) {99, 173, 255}, 500, 240, centered);

		sprintf(buffer, "%d", lines_cleared);

		render_text("Lines:", font, (SDL_Color) {255, 255, 255}, 500, 350, centered);
		render_text(buffer, font, (SDL_Color) {160, 35, 30}, 500, 390, centered);


		render_text("Next:", font, (SDL_Color) {255, 255, 255}, 500, 500, centered);

		int coordinates[4][2];
		get_tetrominos(next_tetromino, coordinates);

		int add_x = 500 - 36;
		if (next_tetromino == TETROMINO_O)
		{
			add_x = 500 - 21;
		}

		if (next_tetromino == TETROMINO_I)
		{
			add_x = 500 - 48;
		}

		for (int i = 0; i < 4; i++)
		{
			render_scaled(drawing_context.tileset, {0, (int) next_tetromino * TILESIZE, TILESIZE, TILESIZE}, coordinates[i][0] * TILESIZE + 0 + (add_x)/3, coordinates[i][1] * TILESIZE + (550)/3, 3);
		}



		render_text("(c) 2025", font, (SDL_Color) {255, 255, 255}, 500, 750, centered);



		SDL_SetRenderDrawColor(sdl_renderer, 50, 50, 50, 255);

		if (gameover)
		{
			render(drawing_context.tileset, {32, 0, 80, 16}, DISPLAY_WIDTH / 2 - 40, DISPLAY_HEIGHT / 2 - 8);
		}

		render_window();

		int frameTicks = SDL_GetTicks() - startTicks;
		if (frameTicks < 1000/REFRESH_RATE) {
			SDL_Delay(1000/REFRESH_RATE - frameTicks);
		}
	}

	return 0;
}

void cleanup()
{
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);

	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (init_sdl() == 1)
	{
		return 1;
	}

	init_drawing_context();

	set_tetromino(&active_tetromino, tiles, tiles_count, next_tetromino);
	next_tetromino = (TetrominoTypes) (rand() % 7);
	tiles_count += 4;

	Mix_Music * music = Mix_LoadMUS("data/soundtrack.wav");
	if (!music)
	{
		printf("Failed to load music: %s\n", Mix_GetError());
	}

	Mix_PlayMusic(music, -1);


	font = TTF_OpenFont("data/nes_font.ttf",18);
	if (!font)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}


	while (run() == 1)
	{
		init_drawing_context();

		tiles_count = 0;
		set_tetromino(&active_tetromino, tiles, tiles_count, next_tetromino);
		next_tetromino = (TetrominoTypes) (rand() % 7);
		tiles_count += 4;

		score = 0;
		lines_cleared = 0;

		run();
	}

	SDL_Quit();

	cleanup();


	return 0;
}
