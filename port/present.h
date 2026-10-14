/* present.h - native composition of the displayed page (see present.c). */
#ifndef PRESENT_H
#define PRESENT_H

#include <stdint.h>
#include "scene.h"

/* Compose the snapshot into a width x 200 canvas of 0xAARRGGBB pixels; width 320 reproduces
   the original page exactly.  Returns 0 when out of memory. */
int present_compose(const SceneSnapshot *snapshot, int width, uint32_t *rgba);

/* The window's picture: composes the shown page when it changed (or the width did) into a
   streaming texture.  *pixels, if given, receives the composed canvas. */
struct SDL_Renderer; struct SDL_Texture;
struct SDL_Texture *present_texture(struct SDL_Renderer *renderer, int width, const uint32_t **pixels);
/* --verify-native: at every page flip compare the native 320 picture with the emulated page. */
void present_set_verify(int on);
void present_verify_shown(void);                /* the toolbox calls it after each flip */
void present_report(void);
void present_shutdown(void);

#endif
