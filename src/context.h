
#pragma once

#include <arnamsneat/arnamsneat.h>

struct _AmstContext {
    SDL_Window* AMST_NONNULL window;
    SDL_Renderer* AMST_NONNULL renderer;
    int32_t windowWidth, windowHeight, rendererWidth, rendererHeight, currentWidth, currentHeight;
    float scaleX, scaleY;
    TTF_Font* AMST_NONNULL font;
    int32_t mouseX, mouseY;
    bool mouseDown;
};
