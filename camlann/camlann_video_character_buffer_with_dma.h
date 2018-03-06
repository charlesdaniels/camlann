/**
 * @file camlann_video_character_buffer_with_dma.h
 * @brief Camlann compability shim for NIOS2 character buffer functions.
 * @author Charles Daniels
 */


#ifndef ALTERA_UP_AVALON_VIDEO_CHARACTER_BUFFER_WITH_DMA_H
#define ALTERA_UP_AVALON_VIDEO_CHARACTER_BUFFER_WITH_DMA_H

#ifdef USE_CAMLANN
#define alt_up_char_buffer_dev alt_u32

#include "camlann.h"
#include "camlann_util.h"
#include "camlann_video_backend.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

alt_up_char_buffer_dev alt_up_char_buffer_open_dev(alt_u32*);
void alt_up_char_buffer_clear();
void alt_up_char_buffer_string(alt_u32, char*, alt_u32, alt_u32);

#endif /* USE_CAMLANN */

#endif
