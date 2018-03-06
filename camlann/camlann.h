#ifndef CAMLANN_H
#define CAMLANN_H


////////10////////20////////30// CONFIGURATION /50////////60////////70////////80

#define US_PER_SECOND 1000000.0
#define MS_PER_SECOND 1000
#define US_PER_MS 1000

#define USER_MAIN user_main
/* size of the virtual VGA buffer */
#define CAMLANN_VGA_BUFFER_HEIGHT 240
#define CAMLANN_VGA_BUFFER_WIDTH  320
/* pixels on the SDL texture per pixel in the VGA buffer */
#define CAMLANN_VGA_SCALE 2
/* size of the SDL texture / window for Camlann */
#define CAMLANN_VIDEO_HEIGHT CAMLANN_VGA_BUFFER_HEIGHT * CAMLANN_VGA_SCALE + 100
#define CAMLANN_VIDEO_WIDTH  CAMLANN_VGA_BUFFER_WIDTH  * CAMLANN_VGA_SCALE
/* top left corner of the virtual VGA buffer */
#define CAMLANN_VGA_BUFFER_ROW 0
#define CAMLANN_VGA_BUFFER_COL 0
/* target FPS, higher will produce smoother rendering but run slower, due to
 * more redraws */
#define CAMLANN_TARGET_FPS 60.0
#define CAMLANN_RENDER_INTERVAL ((1.0 / CAMLANN_TARGET_FPS) * MS_PER_SECOND)
/* poll the clock every this many rows, possibly implying a redraw */
#define CAMLANN_CLOCK_ROWS 5
#define CAMLANN_TTF_FONT "LiberationMono-Regular.ttf"
/* TTF font size *NOT* pixels per character */
#define CAMLANN_TTF_SIZE 12
/* desired number of rows and columns of text */
#define CAMLANN_TEXT_ROWS 60
#define CAMLANN_TEXT_COLS 80
/* ms to sleep after frame redraw - should be less than CAMLANN_RENDER_INTERVAL
 * */
#define CAMLANN_REDRAW_SLEEP 1

/* The Altera NIOS2 BSP character buffer API positions text by characters, not
 * pixels, these factors allow us to translate into absolute pixel positions on
 * the SDL screen */
#define CAMLANN_PIXELS_PER_ROW ((float) CAMLANN_VGA_BUFFER_HEIGHT * \
				(float) CAMLANN_VGA_SCALE) / \
			       ((float) CAMLANN_TEXT_ROWS)
#define CAMLANN_PIXELS_PER_COL ((float) CAMLANN_VGA_BUFFER_WIDTH * \
				(float) CAMLANN_VGA_SCALE) / \
			       ((float) CAMLANN_TEXT_COLS)

////////10////////20////////30// COMPATIBILITY /50////////60////////70////////80
// not all C dialects have M_PI in math
#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

////////10////////20////////30//// INCLUDES ////50////////60////////70////////80
#ifdef USE_CAMLANN

#include "camlann_types.h"
#include "camlann_pio_regs.h"
#include "camlann_system.h"
#include "camlann_video_character_buffer_with_dma.h"
#include "camlann_video_pixel_buffer_dma.h"

#else

#include "alt_types.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#endif /* USE_CAMLANN */

#endif /* CAMLANN_H */
