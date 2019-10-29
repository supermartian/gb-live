/*
 * sdl_renderer.c
 * Copyright (C) 2019 martian <martian@Martian-sys>
 *
 * Distributed under terms of the MIT license.
 */

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "gameboy.h"
#include "sdl_renderer.h"

static TTF_Font *font = NULL;

static void gb_SDL_render(void *aux, void *pixels);

static SDL_Renderer *gb_SDL_Renderer;

static void gb_SDL_render(void *aux, void *pixels)
{
	SDL_Renderer *renderer = (SDL_Renderer *)aux;
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	return;
}

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

static void render_text(SDL_Renderer *renderer, const char *strings, int x, int y)
{
	int w, h;
	/* Font color */
	SDL_Color text_color = { 255, 255, 255 };
	/* Font geometry */
	SDL_Rect dstrect = {0};
	SDL_Surface *message = NULL;
	SDL_Texture *texture = NULL;

	TTF_SizeUTF8(font, strings, &w, &h);
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

static void destroy_graphics(SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

static int poll_event(SDL_Renderer *renderer, struct gb_event *ev)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		return 1;

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	memset(ev->keys, 0, sizeof(ev->keys));

	if (state[SDL_SCANCODE_A]) {
		ev->keys[GB_LEFT] = 1;
	}

	if (state[SDL_SCANCODE_S]) {
		ev->keys[GB_DOWN] = 1;
	}

	if (state[SDL_SCANCODE_D]) {
		ev->keys[GB_RIGHT] = 1;
	}

	if (state[SDL_SCANCODE_W]) {
		ev->keys[GB_UP] = 1;
	}

	if (state[SDL_SCANCODE_U]) {
		ev->keys[GB_A] = 1;
	}

	if (state[SDL_SCANCODE_I]) {
		ev->keys[GB_B] = 1;
	}

	if (state[SDL_SCANCODE_Z]) {
		ev->keys[GB_SELECT] = 1;
	}

	if (state[SDL_SCANCODE_X]) {
		ev->keys[GB_START] = 1;
	}

	return 0;
}

static int show_event(SDL_Renderer *renderer, struct gb_event *ev)
{
	if (ev->keys[GB_UP]) {
		render_text(renderer, "Up", 800, 0);
	}

	if (ev->keys[GB_DOWN]) {
		render_text(renderer, "Down", 800, 30);
	}

	if (ev->keys[GB_LEFT]) {
		render_text(renderer, "Left", 760, 15);
	}

	if (ev->keys[GB_RIGHT]) {
		render_text(renderer, "Right", 830, 15);
	}

	if (ev->keys[GB_A]) {
		render_text(renderer, "A", 760, 40);
	}

	if (ev->keys[GB_B]) {
		render_text(renderer, "B", 800, 40);
	}

	if (ev->keys[GB_SELECT]) {
		render_text(renderer, "Select", 760, 60);
	}

	if (ev->keys[GB_START]) {
		render_text(renderer, "Start", 800, 60);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	struct gb *gb_instance;
	struct gb_event gb_event;
	struct gb_renderer gb_sdl_renderer;

	if (init_graphics(&gb_SDL_Renderer)) {
		return 1;
	}

	if (gb_SDL_Renderer == NULL) {
		return 1;
	}

	gb_instance = malloc(sizeof(struct gb));
	gb_init(gb_instance);

	gb_sdl_renderer.render = gb_SDL_render;
	gb_sdl_renderer.aux = gb_SDL_Renderer;
	gb_instance->interface.renderer = &gb_sdl_renderer;

	while (1) {
		if (poll_event(gb_SDL_Renderer, &gb_event) == 1) {
			break;
		}

		show_event(gb_SDL_Renderer, &gb_event);
		gb_show_state(gb_instance);
		gb_trigger_event(gb_instance, &gb_event);
		gb_render(gb_instance);
	}

	destroy_graphics(gb_SDL_Renderer);
	gb_destroy(gb_instance);
	free(gb_instance);
	return 0;
}
