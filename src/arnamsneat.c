/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "arnamsneat.h"
#include "defs.h"

struct _AmstContext {
    SDL_Window* AMST_NONNULL window;
    SDL_Renderer* AMST_NONNULL renderer;
    int32_t windowWidth, windowHeight, rendererWidth, rendererHeight, currentWidth, currentHeight;
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

static void updateSizes(AmstContext* AMST_NONNULL context) {
    SDL_GetWindowSize(context->window, &(context->windowWidth), &(context->windowHeight));
    SDL_GetRendererOutputSize(context->renderer, &(context->rendererWidth), &(context->rendererHeight));

    context->scaleX = (float) context->rendererWidth / (float) context->windowWidth;
    context->scaleY = (float) context->rendererHeight / (float) context->windowHeight;

    SDL_RenderSetScale(context->renderer, context->scaleX, context->scaleY);
    context->scaleFont = context->scaleY;
}

AmstContext* AMST_NULLABLE amstContextCreate(
    SDL_Window* AMST_NONNULL window,
    SDL_Renderer* AMST_NONNULL renderer,
    TTF_Font* AMST_NONNULL font
) {
    defsAssert(gInitialized);

    AmstContext* context = defsMalloc(sizeof *context);
    context->window = window;
    context->renderer = renderer;
    context->font = font;
    updateSizes(context);

    SDL_Delay(50);

    return context;
}

void amstProcessEvent(SDL_Event* AMST_NONNULL event) {
    defsAssert(gInitialized);
    DEFS_USED(event);
}

void amstPrepareToDraw(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    SDL_GetWindowSizeInPixels(context->window, &(context->currentWidth), &(context->currentHeight));
    SDL_RenderClear(context->renderer);
}

void amstDrawAll(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    SDL_RenderPresent(context->renderer);
}

void amstGetCurrentSizes(AmstContext* AMST_NONNULL context, int32_t* AMST_NONNULL width, int32_t* AMST_NONNULL height) {
    defsAssert(gInitialized);
    *width = context->currentWidth;
    *height = context->currentHeight;
}

void amstContextDestroy(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    defsFree(context);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void amstGetButtonMetrics(
    AmstContext* AMST_NONNULL context,
    AmstButton* AMST_NONNULL button,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);
}

void amstDrawButton(AmstContext* AMST_NONNULL context, AmstButton* AMST_NONNULL button) {
    defsAssert(gInitialized);

}
