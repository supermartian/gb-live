/*
 * main.c
 * Copyright (C) 2019 martian <martian@Martian-sys>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

TTF_Font *font = NULL;

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

	if (TTF_Init() == -1) {
		return 1;
	}

	font = TTF_OpenFont("FreeMono.ttf", 16);

	SDL_SetWindowTitle(window,
			"My Gameboy");

	return 0;
}

static void destroy_graphics(SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

static void render_text(SDL_Renderer *renderer, const char *strings, int x, int y, int w, int h)
{
	/* Font color */
	SDL_Color text_color = { 255, 255, 255 };
	/* Font geometry */
	SDL_Rect dstrect = {0};
	SDL_Surface *message = NULL;
	SDL_Texture *texture = NULL;

	message = TTF_RenderText_Solid(font, strings, text_color);
	if (message == NULL) {
		printf("invalid TTF\n");
		return;
	}

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = w;
	dstrect.h = h;

	texture = SDL_CreateTextureFromSurface(renderer, message);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(message);
}

static void render_graphics(SDL_Renderer *renderer)
{
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

static int poll_event(SDL_Renderer *renderer)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		return 1;

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_A]) {
		render_text(renderer, "Left", 790, 20, 30, 30);
	}

	if (state[SDL_SCANCODE_S]) {
		render_text(renderer, "Down", 800, 40, 30, 30);
	}

	if (state[SDL_SCANCODE_D]) {
		render_text(renderer, "Right", 820, 20, 40, 30);
	}

	if (state[SDL_SCANCODE_W]) {
		render_text(renderer, "Up", 800, 0, 30, 30);
	}

	return 0;
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
		if (poll_event(renderer) == 1) {
			break;
		}

		render_graphics(renderer);
	}

	destroy_graphics(renderer);
	return 0;
}
