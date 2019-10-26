/*
 * main.c
 * Copyright (C) 2019 martian <martian@Martian-sys>
 *
 * Distributed under terms of the MIT license.
 */

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

static int init_graphics(SDL_Renderer **r)
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
			return 3;
	}

	window = SDL_CreateWindow("SDL_CreateTexture",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					1024, 768,
					SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, 0);

	*r = renderer;
	return 0;
}

static void destroy_graphics(SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

static void render_graphics(SDL_Renderer *renderer)
{
	SDL_RenderPresent(renderer);
}

static int poll_event()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if(event.type == SDL_QUIT)
		return 1;
}

int main(int argc, char *argv[])
{
	SDL_Renderer *renderer = NULL;
	if (init_graphics(&renderer)) {
		/* FUCK! */
		return 1;
	}

	if (renderer == NULL) {
		/* FUCK! */
		return 1;
	}

	while (1) {
		if (poll_event() == 1) {
			break;
		}

		render_graphics(renderer);
	}

	destroy_graphics(renderer);
	return 0;
}
