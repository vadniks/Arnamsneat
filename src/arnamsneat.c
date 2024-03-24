/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "arnamsneat.h"
#include "defs.h"
#include <stdint.h>

struct _AmstContext {
    int32_t windowWidth, windowHeight, rendererWidth, rendererHeight;
    float scaleX, scaleY, scaleFont;
    TTF_Font* AMST_NONNULL font;
};

static defsAtomic bool gInitialized = false;

void amstInit(void) {
    if (gInitialized) return;
    gInitialized = true;
}

void amstSetSdlRendererHints(void) {
    defsAssert(gInitialized);
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "3"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"));
}

AmstContext* AMST_NULLABLE amstContextCreate(
    SDL_Window* AMST_NONNULL window,
    SDL_Renderer* AMST_NONNULL renderer,
    TTF_Font* AMST_NONNULL font
) {
    defsAssert(gInitialized);

    AmstContext* context = defsMalloc(sizeof *context);
    SDL_GetWindowSize(window, &(context->windowWidth), &(context->windowHeight));
    SDL_GetRendererOutputSize(renderer, &(context->rendererWidth), &(context->rendererHeight));
    context->scaleX = (float) context->rendererWidth / (float) context->windowWidth;
    context->scaleY = (float) context->rendererHeight / (float) context->windowHeight;

    SDL_SetWindowMinimumSize(
        window,
        (int) ((float) context->windowWidth * context->scaleX),
        (int) ((float) context->windowHeight * context->scaleY)
    );
    SDL_RenderSetScale(renderer, context->scaleX, context->scaleY);

    context->scaleFont = context->scaleY;
    context->font = font;

    return context;
}

void amstProcessEvents(void) {
    defsAssert(gInitialized);
}

void amstContextDestroy(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    DEFS_USED(context);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}
