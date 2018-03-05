/**
 * @file camlann_video_pixel_buffer_dma.c
 * @brief Camlann compatibility shim for NIOS2 pixel drawing functions.
 * @author Charles Daniels
 */


#include "camlann_video_pixel_buffer_dma.h"

#ifdef USE_CAMLANN

/* Horrible, evil global variables required because we can't expect the
 * caller t omaintain them for us. */
SDL_Surface* camlann_sdl_screen;
SDL_Event    camlann_sdl_event;
int          camlann_last_row = 0;

/**
 * @brief Camlann internal function to render a single pixel on the SDL window.
 *
 * @param screen SDL surface. This will be camlann_sdl_screen.
 * @param x horizontal pixel coordinate
 * @param y vertical pixel coordiante
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 */
void camlann_setpixel(SDL_Surface* screen,
		      int x,
		      int y,
		      Uint8 r,
		      Uint8 g,
		      Uint8 b) {

	Uint32 *pixmem32;
	Uint32 colour;

	colour = SDL_MapRGB( screen->format, r, g, b );

	pixmem32 = (Uint32*) screen->pixels  +
		   (y * camlann_sdl_screen->pitch/4) + x;
	*pixmem32 = colour;
}

/**
 * @brief Flip the screen if needed.
 *
 * Specifically, the screen is only flipped if we have just finished
 * drawing a row. This is a performance optimization, an accurate
 * implementation where every pixel is drawn immediately cases roughly two
 * orders of magnitude slowdown compared to this implementation.
 *
 * @param row The row number in which the most recent pixel was rendered.
 */
inline void camlann_flip_screen(int row) {
	if (camlann_last_row != row ) {
		if (SDL_MUSTLOCK(camlann_sdl_screen)) {
			SDL_UnlockSurface(camlann_sdl_screen);
		}
		SDL_Flip(camlann_sdl_screen);
		camlann_last_row = row;
	}
}

/**
 * @brief initialize camlann_sdl_screen.
 */
void camlann_init_video() {
	camlann_sdl_screen = SDL_SetVideoMode(CAMLANN_VIDEO_WIDTH,
					      CAMLANN_VIDEO_HEIGHT,
					      0,
					      SDL_HWSURFACE);
}

alt_up_pixel_buffer_dma_dev alt_up_pixel_buffer_dma_open_dev(alt_u32 base) {
	camlann_init_video();
	return 1;
}

void alt_up_pixel_buffer_dma_clear_screen (alt_u32 base, alt_u32 foo) {
	camlann_fixme("Ignored request to clear screen.\n");
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

	camlann_setpixel(camlann_sdl_screen, col, row, r, g, b);
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
