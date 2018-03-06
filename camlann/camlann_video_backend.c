/**
 * @file camlann_video_backend.c
 * @brief Camlann video rendering back-end.
 * @author Charles Daniels
 */

#include "camlann_video_backend.h"

#ifdef USE_CAMLANN

/* Horrible, evil global variables required because we can't expect the
 * caller to maintain them for us.
 *
 */
SDL_Renderer* camlann_sdl_renderer;
SDL_Window*   camlann_sdl_window;
SDL_Event     camlann_sdl_event;
SDL_Texture*  camlann_sdl_texture;
SDL_Texture*  camlann_sdl_text_texture;
SDL_Surface*  camlann_sdl_text_surface;
TTF_Font*     camlann_sdl_font;
int           camlann_last_row = 0;
uint64_t      camlann_last_update;

/**
 * @brief Display the specified text in white at the specified absolute pixel
 * position on the screen.
 *
 * @param col
 * @param row
 * @param text
 */
void camlann_display_text(uint32_t col, uint32_t row, char* text) {
	int text_height;
	int text_width;

	SDL_Color color = {255, 255, 255, 0};

	camlann_sdl_text_surface = TTF_RenderText_Solid(camlann_sdl_font,
							text,
							color);

	camlann_sdl_text_texture = \
		SDL_CreateTextureFromSurface(camlann_sdl_renderer,
					     camlann_sdl_text_surface);

	SDL_QueryTexture(camlann_sdl_text_texture,
			 NULL,
			 NULL,
			 &text_width,
			 &text_height);
	SDL_Rect text_region = { col, row, text_width, text_height };

	SDL_RenderCopy(camlann_sdl_renderer,
		       camlann_sdl_text_texture,
		       NULL,
		       &text_region);
	SDL_RenderPresent(camlann_sdl_renderer);
}

/**
 * @brief Retrieve current system time in ms.
 *
 * @return
 */
uint64_t camlann_get_timestamp() {
	struct timeval now;
	gettimeofday(&now, NULL);
	uint64_t timestamp = now.tv_sec * MS_PER_SECOND + \
			     now.tv_usec / US_PER_MS;
	return timestamp;
}

/**
 * @brief Camlann internal function to render a single pixel on the SDL window.
 *
 * @param screen SDL surface. This will be camlann_sdl_surface.
 * @param x horizontal pixel coordinate
 * @param y vertical pixel coordiante
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 */
void camlann_setpixel(int x,
		      int y,
		      uint8_t r,
		      uint8_t g,
		      uint8_t b) {

	SDL_SetRenderDrawColor(camlann_sdl_renderer, r, g, b, 255);
	SDL_RenderDrawPoint(camlann_sdl_renderer, x, y);

}

/**
 * @brief Flip the screen if needed.
 *
 * If at least 1 /
 *
 * @param row The row number in which the most recent pixel was rendered.
 */
inline void camlann_flip_screen(int row) {
	/* we only poll the clock every CAMLANN_CLOCK_ROWs many rows */
	if (((camlann_last_row - row) > CAMLANN_CLOCK_ROWS) |
	   ((camlann_last_row - row)  < - CAMLANN_CLOCK_ROWS)) {

		uint64_t now = camlann_get_timestamp();

		/* check if it's time to render a new frame */
		if ((now - camlann_last_update) > CAMLANN_RENDER_INTERVAL) {

			/* detach the renderer from the texture */
			SDL_SetRenderTarget(camlann_sdl_renderer, NULL);

			/* copy texture into the renderer for display */
			SDL_RenderCopyEx(camlann_sdl_renderer,
					 camlann_sdl_texture,
					 NULL,
					 NULL,
					 0,
					 NULL,
					 SDL_FLIP_NONE);

			/* display contents copied from the texture */
			SDL_RenderPresent(camlann_sdl_renderer);

			/* re-attach the renderer to the texture */
			SDL_SetRenderTarget(camlann_sdl_renderer,
					    camlann_sdl_texture);

			SDL_Delay(CAMLANN_REDRAW_SLEEP);

			/* bookkeeping */
			camlann_last_row = row;
			camlann_last_update = now;
		}
	}
}

/**
 * @brief initialize camlann_sdl_surface.
 */
void camlann_init_video() {
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		camlann_log("Failed to initialize SDL.\n");
		exit(1);
	}

	/* create SDL window for Camlann */
	camlann_sdl_window = SDL_CreateWindow("Camlann VGA Framebuffer",
					      SDL_WINDOWPOS_UNDEFINED,
					      SDL_WINDOWPOS_UNDEFINED,
					      CAMLANN_VIDEO_WIDTH,
					      CAMLANN_VIDEO_HEIGHT,
					      SDL_WINDOW_SHOWN );

	/* And a renderer to draw into it */
	camlann_sdl_renderer = SDL_CreateRenderer(camlann_sdl_window,
						  -1,
						  SDL_RENDERER_ACCELERATED  |
						  SDL_RENDERER_PRESENTVSYNC |
						  SDL_RENDERER_TARGETTEXTURE);

	/* And a texture to draw into the renderer with */
	camlann_sdl_texture = SDL_CreateTexture(camlann_sdl_renderer,
						SDL_PIXELFORMAT_RGBA8888,
						SDL_TEXTUREACCESS_TARGET,
						CAMLANN_VIDEO_WIDTH,
						CAMLANN_VIDEO_HEIGHT);

	if (camlann_sdl_window == NULL) {
		camlann_log("Failed to create SDL window.\n");
		exit(1);
	}

	SDL_SetRenderTarget(camlann_sdl_renderer, camlann_sdl_texture);

	/* clean up everything */
	camlann_last_update = camlann_get_timestamp();
	camlann_last_row = 0;
	SDL_RenderClear(camlann_sdl_renderer);

}

#endif
