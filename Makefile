#
# Makefile
# martian, 2019-10-26 19:33
#
#

CFLAGS = $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --static-libs)
LDFLAGS += -lSDL2_ttf

SOURCES = main.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))

$(OBJS): $(SOURCES)

all: $(OBJS)
	$(CC) $(OBJS) -o main $(LDFLAGS)

clean:
	rm -rf $(OBJS) main

.PHONY:
	all clean
