#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include "drawing_context.h"

#include "globals.h"


typedef enum
{
	left,
	centered,
	right
} TextOrientation;


SDL_Texture * load_texture(const char * file_path, SDL_Renderer * renderer);

void render(SDL_Texture * texture, SDL_Rect img_rect, float p_x, float p_y);

void render_scaled(SDL_Texture * texture, SDL_Rect img_rect, float p_x, float p_y, float render_scale);

void render_text(const char * text, TTF_Font * font, SDL_Color text_color, int x, int y, TextOrientation orientation);

void render_window();

void render_clear();
