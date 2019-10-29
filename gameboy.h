/*
 * gameboy.h
 * Copyright (C) 2019 martian <martian@Martian-sys>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "renderer.h"

enum gb_keys {
	GB_UP = 0,
	GB_LEFT,
	GB_RIGHT,
	GB_DOWN,
	GB_A,
	GB_B,
	GB_SELECT,
	GB_START,
	GB_KEY_MAX
};

struct gb_interface {
	/* 0 key up, 1 key down */
	int keys[GB_KEY_MAX];
	/* graphic renderer */
	struct gb_renderer *renderer;
};

struct gb_event {
	/* 0 key up, 1 key down */
	int keys[GB_KEY_MAX];
};

struct gb_hardware {
};

struct gb {
	/* Interact with the user */
	struct gb_interface interface;
	/* Emulation of the hardware */
	struct gb_hardware hardware;
};

int gb_init(struct gb *gb_instance);
int gb_trigger_event(struct gb *gb_instance, struct gb_event *ev);
int gb_render(struct gb *gb_instance);
int gb_show_state(struct gb *gb_instance);
int gb_destroy(struct gb *gb_instance);

#endif /* !GAMEBOY_H */
