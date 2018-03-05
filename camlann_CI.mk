# this makefile is used only for testing that Camlann compiles for CI purposes
CC=gcc
SDL_FLAGS=$(shell sdl2-config --libs)
CFLAGS= -std=c99 -fno-builtin -O0 -DUSE_CAMLANN -DCAMLANN_CI -Wall -Wextra -pedantic -Werror
CLINK=-lm $(SDL_FLAGS)

CAMLANN_PREFIX=./camlann/
CAMLANN_OBJECTS=camlann_video_character_buffer_with_dma.o camlann_video_pixel_buffer_dma.o camlann_pio_regs.o camlann_main.o camlann_util.o
BINARY_NAME=camlann_bin

$(BINARY_NAME): $(CAMLANN_OBJECTS)
	$(CC) $(CFLAGS) $^ $(CLINK) -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^ $(CLINK)

%.o: $(CAMLANN_PREFIX)/%.c $(CAMLANN_PREFIX)/%.h
	$(CC) $(CFLAGS) -c $^ $(CLINK)

clean:
	rm -f *.o
	rm -f *.gch
	rm -f $(CAMLANN_PREFIX)/*.o
	rm -f $(CAMLANN_PREFIX)/*.gch
	rm -f camlann_bin