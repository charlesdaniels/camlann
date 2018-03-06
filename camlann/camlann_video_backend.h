/**
 * @file camlann_video_backend.h
 * @brief Camlann video rendering back-end.
 * @author Charles Daniels
 */

#ifndef CAMLANN_VIDEO_BACKEND_H
#define CAMLANN_VIDEO_BACKEND_H

#include "camlann.h"

# ifdef USE_CAMLANN

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

uint64_t camlann_get_timestamp();
void camlann_setpixel(int, int, Uint8, Uint8, Uint8);
void camlann_flip_screen(int);
void camlann_init_video();
void camlann_display_text(uint32_t col, uint32_t row, char* text);

extern SDL_Renderer* camlann_sdl_renderer;
extern SDL_Window*   camlann_sdl_window;
extern SDL_Event     camlann_sdl_event;
extern SDL_Texture*  camlann_sdl_texture;
extern SDL_Texture*  camlann_sdl_text_texture;
extern SDL_Surface*  camlann_sdl_text_surface;
extern TTF_Font*     camlann_sdl_font;
extern int           camlann_last_row;
extern uint64_t      camlann_last_update;

#endif /* USE_CAMLANN */


#endif /* CAMLANN_VIDEO_BACKEND_H */
