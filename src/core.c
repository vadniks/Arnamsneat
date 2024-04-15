/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <arnamsneat/core.h>
#include "internal.h"
#include "context.h"
#include "defs.h"

void amstInit(void) {
    if (gInitialized) return;
    gInitialized = true;
}

bool amstInitialized(void) { return gInitialized; }

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
    updateSizes(context);
    context->font = font;
    context->mouseX = 0;
    context->mouseY = 0;
    context->mouseDown = false;
    context->lastDrawnWidth = 0;
    context->lastDrawnHeight = 0;
    context->keyboardInputting = false;
    SDL_memset(context->keyboardInput, 0, AMST_MAX_KEYBOARD_INPUT_SIZE);
    context->keyboardInputSize = 0;
    context->activeField = nullptr;

    return context;
}

void amstProcessEvent(AmstContext* AMST_NONNULL context, SDL_Event* AMST_NONNULL event) {
    defsAssert(gInitialized);

    switch (event->type) {
        case SDL_MOUSEMOTION:
            context->mouseX = event->motion.x;
            context->mouseY = event->motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            context->mouseDown = true;
            break;
        case SDL_MOUSEBUTTONUP:
            context->mouseDown = false;
            break;
        case SDL_KEYDOWN:
            context->keyboardInputting = true;
            break;
        case SDL_KEYUP:
            context->keyboardInputting = false;
            break;
        case SDL_TEXTINPUT:
            defsAssert(context->keyboardInputting);
            if (context->keyboardInputSize >= AMST_MAX_KEYBOARD_INPUT_SIZE) break;

            const int32_t size = (int32_t) SDL_strlen(event->text.text);
            SDL_memcpy(context->keyboardInput + context->keyboardInputSize, event->text.text, size);
            context->keyboardInputSize += size;
            break;
        case SDLK_BACKSPACE:
            if (context->keyboardInputting)
                ;
            break;
    }
}

void amstPrepareToDraw(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    SDL_GetWindowSizeInPixels(context->window, &(context->currentWidth), &(context->currentHeight));
    SDL_SetRenderDrawColor(context->renderer, 50, 50, 50, 255);
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

void amstGetLastDrawnSizes(AmstContext* AMST_NONNULL context, int32_t* AMST_NONNULL width, int32_t* AMST_NONNULL height) {
    defsAssert(gInitialized);
    *width = context->lastDrawnWidth;
    *height = context->lastDrawnHeight;
}

void amstContextDestroy(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    defsFree(context);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}
