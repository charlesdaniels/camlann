/**
 * @file camlann_video_pixel_buffer_dma.c
 * @brief Camlann compatibility shim for NIOS2 pixel drawing functions.
 * @author Charles Daniels
 */


#include "camlann_video_pixel_buffer_dma.h"

#ifdef USE_CAMLANN

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
	Uint32 col_render, row_render;
	r = color >> 16;
	g = color >> 8;
	b = color;

	#ifdef CAMLANN_CI
	/* prevent -Wextra from yelling at us for an unused parameter */
	printf("%x", base);
	#endif

	/* this mess allows us to render multiple pixels per pixel which is
	 * sent to this function - by default 2 pixels per pixel */
	for (col_render =  (col * CAMLANN_VGA_SCALE) + CAMLANN_VGA_BUFFER_COL ;
	     col_render <= (col * CAMLANN_VGA_SCALE) + CAMLANN_VGA_BUFFER_COL +
			   CAMLANN_VGA_SCALE ;
	     col_render ++) {

		for (row_render =  (row * CAMLANN_VGA_SCALE) +
				   CAMLANN_VGA_BUFFER_ROW ;
		     row_render <= (row * CAMLANN_VGA_SCALE) +
				   CAMLANN_VGA_BUFFER_ROW +
				   CAMLANN_VGA_SCALE ;
		     row_render ++) {

			/* make sure we don't to outside of the VGA buffer
			 * drawing area */
			if (row_render >  CAMLANN_VGA_BUFFER_ROW +
					 (CAMLANN_VGA_BUFFER_HEIGHT *
					  CAMLANN_VGA_SCALE)) {
				continue;
			}
			if (col_render >  CAMLANN_VGA_BUFFER_COL +
					 (CAMLANN_VGA_BUFFER_WIDTH *
					  CAMLANN_VGA_SCALE)) {
				continue;
			}
			camlann_setpixel(col_render, row_render, r, g, b);
		}
	}
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
