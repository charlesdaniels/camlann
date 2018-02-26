#ifndef CAMLANN_H
#define CAMLANN_H


////////10////////20////////30// CONFIGURATION /50////////60////////70////////80
#define USER_MAIN user_main
#define CAMLANN_VIDEO_HEIGHT 240
#define CAMLANN_VIDEO_WIDTH  320


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
