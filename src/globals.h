#pragma once
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;


const int TILESIZE = 8;

const int RENDER_SCALE = 5;

const int DISPLAY_WIDTH = SCREEN_WIDTH / RENDER_SCALE;

const int DISPLAY_HEIGHT = SCREEN_HEIGHT / RENDER_SCALE;

const int GAME_FIELD_WIDTH = DISPLAY_WIDTH - 40;

const int GAME_FIELD_HEIGHT = DISPLAY_HEIGHT;

const int REFRESH_RATE = 60;


