#pragma once
#include <SDL.h>

typedef struct
{
	SDL_Renderer * renderer;
	SDL_Texture * tileset;

} Drawing_Context;

extern Drawing_Context drawing_context;