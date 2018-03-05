/**
 * @file camlann_video_character_buffer_with_dma.c
 * @brief Camlann compaitibilty shim for NIOS2 character buffer functions.
 * @author Charles Daniels
 */

#ifdef USE_CAMLANN

#include "camlann_video_character_buffer_with_dma.h"

TTF_Font *camlann_font;

/**
 * @brief Provides compatibility with the Altera BSP, but does nothing.
 *
 * @param base Ignored by Camlann.
 *
 * @return
 */
alt_up_char_buffer_dev alt_up_char_buffer_open_dev(alt_u32 base) {
	camlann_init_char();
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
	/* char* msg; */
        /*  */
	/* msg = (char*) malloc(1204 * sizeof(char)); */
	/* sprintf(msg, */
	/*         "request to render text '%s' at %i, %i via device at %x\n", */
	/*         text, col, row, base); */
	/* camlann_log(msg); */
	SDL_Surface *text_surface;
	SDL_Color text_color = {255, 255, 255};
	text_surface = TTF_RenderText_Solid(camlann_font, text, text_color);
	camlann_blit_surface(text_surface);
}

void camlann_init_char() {
	camlann_log("Initializing character buffer\n");
	if (TTF_Init() != 0) {
		camlann_log("Failed to initalize TTF.\n");
		exit(1);
	}

	camlann_font = TTF_OpenFont("FreeSans.ttf", 24);
	if (camlann_font == NULL) {
		camlann_log("Failed to open FreeSans.ttf\n");
		exit(1);
	}

}

#endif

