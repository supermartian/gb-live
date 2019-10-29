/*
 * gameboy.c
 * Copyright (C) 2019 martian <martian@Martian-sys>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdlib.h>
#include "gameboy.h"

int gb_init(struct gb *gb_instance)
{
	return 0;
}

int gb_trigger_event(struct gb *gb_instance, struct gb_event *ev)
{
	return 0;
}

int gb_render(struct gb *gb_instance)
{
	struct gb_renderer *r = gb_instance->interface.renderer;

	r->render(r->aux, NULL);
	return 0;
}

int gb_show_state(struct gb *gb_instance)
{
	return 0;
}

int gb_destroy(struct gb *gb_instance)
{
	return 0;
}
