/**
 * @file camlann_video_character_buffer_with_dma.c
 * @brief Camlann compaitibilty shim for NIOS2 character buffer functions.
 * @author Charles Daniels
 */

#ifdef USE_CAMLANN

#include "camlann_video_character_buffer_with_dma.h"

/**
 * @brief Provides compatibility with the Altera BSP, but does nothing.
 *
 * @param base Ignored by Camlann.
 *
 * @return
 */
alt_up_char_buffer_dev alt_up_char_buffer_open_dev(alt_u32* base) {
	char* msg;

	msg = (char*) malloc(1204 * sizeof(char));
	sprintf(msg,
		"Request to open char buffer device at %x\n",
		base);
	camlann_verbose(msg);
	free(msg);

	TTF_Init();

	camlann_sdl_font = TTF_OpenFont("arial.ttf", 25);

	/* this does nothing, but makes GCC and the wrapped code happy */
	return 0;
}


/**
 * @brief Provides compatibility with the Altera BSP, clears character
 * overlay buffer.
 */
void alt_up_char_buffer_clear() {
	camlann_fixme("Ignored request to clear char buffer.\n");

}

/**
 * @brief Ostensibly, this would render text onto the drawing area, but for
 * now it just prints it to the console.
 *
 * Note that 0,0 is the top left corner of the character buffer region.
 *
 * @param base Ignored, only provided for compatibility with the Altera BSP.
 * @param text The text to display.
 * @param col Column on the character buffer at which to render the text.
 * @param row Row on the character buffer.
 */
void alt_up_char_buffer_string(alt_u32 base,
			       char* text,
			       alt_u32 col,
			       alt_u32 row) {
	char* msg;

	msg = (char*) malloc(1204 * sizeof(char));
	sprintf(msg,
		"request to render text '%s' at %i, %i via device at %x\n",
		text, col, row, base);
	camlann_log(msg);
	SDL_Color color = {255, 255, 255};
	camlann_sdl_text_surface = TTF_RenderText_Solid(camlann_sdl_font,
							text,
							color);

	camlann_sdl_text_texture = \
		SDL_CreateTextureFromSurface(camlann_sdl_renderer,
					     camlann_sdl_text_surface);
	SDL_RenderCopy(camlann_sdl_renderer, camlann_sdl_text_texture, NULL, NULL);
	SDL_RenderPresent(camlann_sdl_renderer);

}

#endif
