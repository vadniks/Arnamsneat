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

uint32_t amstBackgroundColor = AMST_BACKGROUND_COLOR;
uint32_t amstForegroundColor = AMST_FOREGROUND_COLOR;
uint32_t amstHoverColor = AMST_HOVER_COLOR;
uint32_t amstActiveColor = AMST_ACTIVE_COLOR;
uint32_t amstSecondaryColor = AMST_SECONDARY_COLOR;

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

AmstContext* AMST_NULLABLE amstCreateContext(
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
    context->keyboardInputErasing = false;
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
            if (event->key.keysym.sym == SDLK_BACKSPACE)
                context->keyboardInputErasing = true;
            break;
        case SDL_KEYUP:
            context->keyboardInputting = false;
            context->keyboardInputErasing = false;
            break;
        case SDL_TEXTINPUT:
            context->keyboardInputting = true;
            defsAssert(context->keyboardInputting);

            const int32_t size = (int32_t) SDL_strlen(event->text.text);
            defsAssert(size > 0 && size <= (int32_t) sizeof(int32_t));

            context->nextGlyph = 0;
            SDL_memcpy(&(context->nextGlyph), event->text.text, size);
            SDL_Log("0x%08x", SDL_Swap32(context->nextGlyph));
            break;
    }
}

void amstPrepareToDraw(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    const SDL_Color background = amstMakeColor(amstBackgroundColor);

    SDL_GetWindowSizeInPixels(context->window, &(context->currentWidth), &(context->currentHeight));
    SDL_SetRenderDrawColor(context->renderer, background.r, background.g, background.b, background.a);
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

SDL_Color amstMakeColor(AmstColor color) {
    const int32_t probe = 0x12345678;
    defsAssert(*((defsByte*) &probe) == 0x78);

    return (SDL_Color) {
        (color >> 0) & 0xff,
        (color >> 8) & 0xff,
        (color >> 16) & 0xff,
        (color >> 24) & 0xff,
    };
}

void amstDestroyContext(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    defsFree(context);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}
