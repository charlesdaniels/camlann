/**
 * @file camlann_video_pixel_buffer_dma.h
 * @author Charles Daniels
 * @brief Camlann compatibility shim for NIOS2 pixel drawing functions.
 */


#ifndef ALTERA_UP_AVALON_VIDEO_PIXEL_BUFFER_DMA_H
#define ALTERA_UP_AVALON_VIDEO_PIXEL_BUFFER_DMA_H

#ifdef USE_CAMLANN
#include "camlann.h"
#include "camlann_video_backend.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/* typedef alt_u32 alt_up_pixel_buffer_dma_dev; */
#define alt_up_pixel_buffer_dma_dev alt_u32

alt_up_pixel_buffer_dma_dev alt_up_pixel_buffer_dma_open_dev(char*);
void alt_up_pixel_buffer_dma_clear_screen (alt_u32, alt_u32);
void alt_up_pixel_buffer_dma_draw(alt_u32, alt_u32, alt_u32, alt_u32);

#endif /* USE_CAMLANN */
#endif
