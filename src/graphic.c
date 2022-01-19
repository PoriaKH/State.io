//
// Created by PoriaKP on 1/19/2022.
//
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "graphic.h"

void drawBox(SDL_Renderer *sdlRenderer, int x, int y, Uint32 color) {
    Sint16 width1 = 1000 * y / 8;
    Sint16 height1 = 800 * x / 8;
    boxColor(sdlRenderer, width1, height1, width1 + 1000 / 8, height1 + 800 / 8, color);
}