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
alt_up_char_buffer_dev alt_up_char_buffer_open_dev(alt_u32 base) {
	char* msg;

	msg = (char*) malloc(1204 * sizeof(char));
	sprintf(msg,
		"Ignored request to open char buffer device at %x\n",
		base);

	camlann_log(msg);
	return 1;
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
}

#endif