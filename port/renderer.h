/* SDL_Renderer implementation of the captured 320x200 gameplay picture. */
#ifndef DUKE_NATIVE_RENDERER_H
#define DUKE_NATIVE_RENDERER_H

#include "capture.h"

#include <SDL3/SDL.h>
#include <stdint.h>

int native_renderer_init(SDL_Renderer *renderer);
void native_renderer_shutdown(void);
SDL_Texture *native_renderer_render(const CaptureFrame *frame,
                                    int canvas_width,
                                    uint32_t *readback_argb);

#endif
