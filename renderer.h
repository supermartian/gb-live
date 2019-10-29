/*
 * renderer.h
 * Copyright (C) 2019 martian <martian@Martian-sys>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef RENDERER_H
#define RENDERER_H

struct gb_renderer {
	void (*render)(void *aux, void *pixels);
	void *aux;
};

#endif /* !RENDERER_H */
