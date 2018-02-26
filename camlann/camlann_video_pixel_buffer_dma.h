/**
 * @file camlann_video_pixel_buffer_dma.h
 * @author Charles Daniels
 * @brief Camlann compatibility shim for NIOS2 pixel drawing functions.
 */


#ifndef ALTERA_UP_AVALON_VIDEO_PIXEL_BUFFER_DMA_H
#define ALTERA_UP_AVALON_VIDEO_PIXEL_BUFFER_DMA_H

#include "camlann.h"
#include <stdio.h>
#include <SDL/SDL.h>

/* typedef alt_u32 alt_up_pixel_buffer_dma_dev; */
#define alt_up_pixel_buffer_dma_dev alt_u32

alt_up_pixel_buffer_dma_dev alt_up_pixel_buffer_dma_open_dev(alt_u32);
void alt_up_pixel_buffer_dma_clear_screen (alt_u32, alt_u32);
void alt_up_pixel_buffer_dma_draw(alt_u32, alt_u32, alt_u32, alt_u32);
void camlann_setpixel(SDL_Surface*, int, int, Uint8, Uint8, Uint8);
void camlann_flip_screen(int);
void camlann_init_video();

#endif
