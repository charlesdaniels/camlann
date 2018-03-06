/**
 * @file camlann_video_pixel_buffer_dma.h
 * @author Charles Daniels
 * @brief Camlann compatibility shim for NIOS2 pixel drawing functions.
 */


#ifndef ALTERA_UP_AVALON_VIDEO_PIXEL_BUFFER_DMA_H
#define ALTERA_UP_AVALON_VIDEO_PIXEL_BUFFER_DMA_H

#ifdef USE_CAMLANN
#include "camlann.h"
#include <stdio.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/* typedef alt_u32 alt_up_pixel_buffer_dma_dev; */
#define alt_up_pixel_buffer_dma_dev alt_u32

alt_up_pixel_buffer_dma_dev alt_up_pixel_buffer_dma_open_dev(char*);
void alt_up_pixel_buffer_dma_clear_screen (alt_u32, alt_u32);
void alt_up_pixel_buffer_dma_draw(alt_u32, alt_u32, alt_u32, alt_u32);

void camlann_setpixel(int, int, Uint8, Uint8, Uint8);
void camlann_flip_screen(int);
void camlann_init_video();

extern SDL_Renderer* camlann_sdl_renderer;
extern SDL_Window*   camlann_sdl_window;
extern SDL_Event     camlann_sdl_event;
extern SDL_Texture*  camlann_sdl_texture;
extern SDL_Texture*  camlann_sdl_text_texture;
extern SDL_Surface*  camlann_sdl_text_surface;
extern TTF_Font*     camlann_sdl_font;

#endif /* USE_CAMLANN */
#endif
