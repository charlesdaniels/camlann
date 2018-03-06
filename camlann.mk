CC=gcc
SDL_LIBS=$(shell sdl2-config --libs)
SDL_FLAGS=$(shell sdl2-config --cflags)
CFLAGS= -std=c99 -fno-builtin -O0 -DUSE_CAMLANN $(SDL_FLAGS)
CLINK=-lm $(SDL_LIBS) -lSDL2_ttf

CAMLANN_PREFIX=./camlann/
CAMLANN_OBJECTS=camlann_video_character_buffer_with_dma.o camlann_video_pixel_buffer_dma.o camlann_pio_regs.o camlann_main.o camlann_util.o
NIOS2_OBJECTS=##NIOS2OBJECTS##
BINARY_NAME=camlann_bin

$(BINARY_NAME): $(CAMLANN_OBJECTS) $(NIOS2_OBJECTS)
	$(CC) $^ $(CFLAGS) $(CLINK) -o $@

%.o: %.c %.h
	$(CC) $^ $(CFLAGS) $(CLINK) -c

%.o: $(CAMLANN_PREFIX)/%.c $(CAMLANN_PREFIX)/%.h
	$(CC) $^ $(CFLAGS) $(CLINK) -c

clean:
	rm -f *.o
	rm -f *.gch
	rm -f $(CAMLANN_PREFIX)/*.o
	rm -f $(CAMLANN_PREFIX)/*.gch
	rm -f camlann_bin
