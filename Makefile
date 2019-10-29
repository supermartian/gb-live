#
# Makefile
# martian, 2019-10-26 19:33
#
#

CFLAGS = $(shell sdl2-config --cflags)
CFLAGS += -DRENDERER_SDL2
LDFLAGS = $(shell sdl2-config --static-libs)
LDFLAGS += -lSDL2_ttf

SOURCES = gameboy.c gb_sdl.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))

TARGET = gb-live

$(OBJS): $(SOURCES)

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf $(OBJS) $(TARGET)

.PHONY:
	all clean

.DEFAULT_GOAL := all
