/**
 * @file camlann_video_pixel_buffer_dma.c
 * @brief Camlann compatibility shim for NIOS2 pixel drawing functions.
 * @author Charles Daniels
 */


#include "camlann_video_pixel_buffer_dma.h"

#ifdef USE_CAMLANN

/* Horrible, evil global variables required because we can't expect the
 * caller to maintain them for us.
 *
 * TODO; should move these and camlann video backend to it's own file, since
 * some stuff from here interacts with things from the character buffer code.
 */
SDL_Renderer* camlann_sdl_renderer;
SDL_Window*   camlann_sdl_window;
SDL_Event     camlann_sdl_event;
SDL_Texture*  camlann_sdl_texture;
SDL_Texture*  camlann_sdl_text_texture;
SDL_Surface*  camlann_sdl_text_surface;
TTF_Font*     camlann_sdl_font;
int           camlann_last_row = 0;
Uint64        camlann_last_update;

/**
 * @brief Retrieve current system time in ms.
 *
 * @return
 */
Uint64 camlann_get_timestamp() {
	struct timeval now;
	gettimeofday(&now, NULL);
	Uint64 timestamp = now.tv_sec * MS_PER_SECOND + \
			   now.tv_usec / US_PER_MS;
	return timestamp;
}

/**
 * @brief Camlann internal function to render a single pixel on the SDL window.
 *
 * @param screen SDL surface. This will be camlann_sdl_surface.
 * @param x horizontal pixel coordinate
 * @param y vertical pixel coordiante
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 */
void camlann_setpixel(int x,
		      int y,
		      Uint8 r,
		      Uint8 g,
		      Uint8 b) {

	SDL_SetRenderDrawColor(camlann_sdl_renderer, r, g, b, 255);
	SDL_RenderDrawPoint(camlann_sdl_renderer, x, y);

}

/**
 * @brief Flip the screen if needed.
 *
 * If at least 1 /
 *
 * @param row The row number in which the most recent pixel was rendered.
 */
inline void camlann_flip_screen(int row) {
	/* we only poll the clock every CAMLANN_CLOCK_ROWs many rows */
	if (((camlann_last_row - row) > CAMLANN_CLOCK_ROWS) |
	   ((camlann_last_row - row)  < - CAMLANN_CLOCK_ROWS)) {

		Uint64 now = camlann_get_timestamp();

		/* check if it's time to render a new frame */
		if ((now - camlann_last_update) > CAMLANN_RENDER_INTERVAL) {

			/* detach the renderer from the texture */
			SDL_SetRenderTarget(camlann_sdl_renderer, NULL);

			/* copy texture into the renderer for display */
			SDL_RenderCopyEx(camlann_sdl_renderer,
					 camlann_sdl_texture,
					 NULL,
					 NULL,
					 0,
					 NULL,
					 SDL_FLIP_NONE);

			/* display contents copied from the texture */
			SDL_RenderPresent(camlann_sdl_renderer);

			/* re-attach the renderer to the texture */
			SDL_SetRenderTarget(camlann_sdl_renderer,
					    camlann_sdl_texture);

			/* bookkeeping */
			camlann_last_row = row;
			camlann_last_update = now;
		}
	}
}

/**
 * @brief initialize camlann_sdl_surface.
 */
void camlann_init_video() {
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		camlann_log("Failed to initialize SDL.\n");
		exit(1);
	}

	/* create SDL window for Camlann */
	camlann_sdl_window = SDL_CreateWindow("Camlann VGA Framebuffer",
					      SDL_WINDOWPOS_UNDEFINED,
					      SDL_WINDOWPOS_UNDEFINED,
					      CAMLANN_VIDEO_WIDTH,
					      CAMLANN_VIDEO_HEIGHT,
					      SDL_WINDOW_SHOWN );

	/* And a renderer to draw into it */
	camlann_sdl_renderer = SDL_CreateRenderer(camlann_sdl_window,
						  -1,
						  SDL_RENDERER_ACCELERATED  |
						  SDL_RENDERER_PRESENTVSYNC |
						  SDL_RENDERER_TARGETTEXTURE);

	/* And a texture to draw into the renderer with */
	camlann_sdl_texture = SDL_CreateTexture(camlann_sdl_renderer,
						SDL_PIXELFORMAT_RGBA8888,
						SDL_TEXTUREACCESS_TARGET,
						CAMLANN_VIDEO_WIDTH,
						CAMLANN_VIDEO_HEIGHT);

	if (camlann_sdl_window == NULL) {
		camlann_log("Failed to create SDL window.\n");
		exit(1);
	}

	SDL_SetRenderTarget(camlann_sdl_renderer, camlann_sdl_texture);

	/* clean up everything */
	camlann_last_update = camlann_get_timestamp();
	camlann_last_row = 0;
	SDL_RenderClear(camlann_sdl_renderer);

}

alt_up_pixel_buffer_dma_dev alt_up_pixel_buffer_dma_open_dev(char* base) {
	camlann_init_video();

	char* msg = (char*) malloc(1024 * sizeof(char));
	sprintf(msg, "Initialized screen (@base: %x)\n", base);
	camlann_fixme(msg);
	free(msg);

	/* this does nothing, but makes the wrapped code and also GCC happy */
	return 0;
}

void alt_up_pixel_buffer_dma_clear_screen (alt_u32 base, alt_u32 foo) {
	char* msg = (char*) malloc(1024 * sizeof(char));
	sprintf(msg, "Ignored request to clear screen (@base: %x, ?%x)\n",
		base,
		foo);
	camlann_fixme(msg);
	free(msg);
}

/**
 * @brief Compatibility with the Altera NIOS2 BSP.
 *
 * Note that the Camlann implementation of this function may be slightly
 * inaccurate due to the implementation of camlann_flip_screen() - to be
 * specific, Camlann only updates the screen if the row for this call was not
 * the same as the row for the previous call. This means setting an arbitrary
 * pixel may not cause it to render to the screen immediately.
 *
 * @param base Ignored in Camlann, on the board this is the base address of
 * the DMA controller for the screen's SRAM.
 * @param color Color, represented as a 32 bit int.
 * @param col Column to render pixel at.
 * @param row Row to render pixel at.
 */
void alt_up_pixel_buffer_dma_draw(alt_u32 base,
				  alt_u32 color,
				  alt_u32 col,
				  alt_u32 row) {
	int r, g, b;
	r = color >> 16;
	g = color >> 8;
	b = color;

	#ifdef CAMLANN_CI
	/* prevent -Wextra from yelling at us for an unused parameter */
	printf("%x", base);
	#endif

	camlann_setpixel(col, row, r, g, b);
	camlann_flip_screen(row);

	// if the window is closed / quit, tell SDL to allow it to quit
	while(SDL_PollEvent(&camlann_sdl_event)) {
		switch(camlann_sdl_event.type) {
			case SDL_QUIT:
				exit(0);
		}
	}

}

#endif
