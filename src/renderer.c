#include "renderer.h"

SDL_Texture * load_texture(const char * file_path, SDL_Renderer * renderer)
{
	SDL_Texture * texture = NULL;
	texture = IMG_LoadTexture(renderer, file_path);
	if (texture == NULL)
	{
		printf("Could not load texture\n");
		printf("Error: %s", SDL_GetError());
	}
	return texture;
}

void render(SDL_Texture * texture, SDL_Rect img_rect, float p_x, float p_y)
{
	SDL_Rect src;
	src.x = img_rect.x;
	src.y = img_rect.y;

	src.w = img_rect.w;
	src.h = img_rect.h;

	SDL_Rect dst;
	dst.x = p_x * RENDER_SCALE;
	dst.y = p_y * RENDER_SCALE;
	dst.w = src.w * RENDER_SCALE;
	dst.h = src.h * RENDER_SCALE;

	SDL_RenderCopy(drawing_context.renderer, texture, &src, &dst);
}

void render_scaled(SDL_Texture * texture, SDL_Rect img_rect, float p_x, float p_y, float render_scale)
{
	SDL_Rect src;
	src.x = img_rect.x;
	src.y = img_rect.y;

	src.w = img_rect.w;
	src.h = img_rect.h;

	SDL_Rect dst;
	dst.x = p_x * render_scale;
	dst.y = p_y * render_scale;
	dst.w = src.w * render_scale;
	dst.h = src.h * render_scale;

	SDL_RenderCopy(drawing_context.renderer, texture, &src, &dst);
}


void render_text(const char * text, TTF_Font * font, SDL_Color text_color, int x, int y, TextOrientation orientation)
{
	SDL_Surface * text_surface = TTF_RenderText_Solid(font, text, text_color);
	if (!text_surface) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return;
	}

	SDL_Texture * text_texture = SDL_CreateTextureFromSurface(drawing_context.renderer, text_surface);

	SDL_Rect render_quad = {x, y, text_surface->w, text_surface->h};

	if (orientation == centered)
	{
		render_quad.x = x - text_surface->w / 2;

	}

	if (orientation == right)
	{
		render_quad.x = x - text_surface->w;
	}

	SDL_FreeSurface(text_surface);

	SDL_SetRenderDrawColor(drawing_context.renderer, 0, 0, 0, 255); // Black background

	SDL_RenderCopy(drawing_context.renderer, text_texture, NULL, &render_quad);

	SDL_SetRenderDrawColor(drawing_context.renderer, 50, 50, 50, 255);
}

void render_window()
{
	SDL_RenderPresent(drawing_context.renderer);
}

void render_clear()
{
	SDL_RenderClear(drawing_context.renderer);
}