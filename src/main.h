#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#include "globals.h"

#include "renderer.h"
#include "drawing_context.h"

#include "tetromino.h"
#include "tile.h"

#include <stdlib.h>

#include <time.h>



SDL_Window * sdl_window;

SDL_Renderer * sdl_renderer;



float hireTimeInSeconds();

float deltaTime;

const float timeStep = 0.01f;
float accumulator = 0.0f;
float currentTime = hireTimeInSeconds();

float globalTime;

int all_time = 0;



bool gameover = false;

int TICK_RATE = 2;

int tick_accumilator = 0;
float max_tick_accumilator = REFRESH_RATE / TICK_RATE;


TTF_Font * font;


Tile tiles[256];

int tiles_count = 0;

Tetromino active_tetromino;

TetrominoTypes next_tetromino = TETROMINO_O;

int score = 0;
int lines_cleared = 0;


int init_sdl();

void init_drawing_context();

int run();

void cleanup();

int main(int argc, char* argv[]);


void check_for_lines_cleared();

void clear_line(int y);