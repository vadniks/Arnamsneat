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
    float scaleX, scaleY;
    int32_t fontSize;
    TTF_Font* AMST_NONNULL font;
    int32_t mouseX, mouseY;
    bool mouseDown;
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
    context->fontSize = (int32_t) context->scaleY;
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
    }

    DEFS_USED(event);
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

void amstContextDestroy(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    defsFree(context);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void amstGetTextMetrics(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);
    TTF_SizeUTF8(context->font, text, width, height);
}

static SDL_Texture* AMST_NONNULL renderText(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    SDL_Color color,
    int32_t* AMST_NULLABLE width,
    int32_t* AMST_NULLABLE height
) {
    SDL_Surface* surface = TTF_RenderUTF8_Solid(context->font, text, color);

    if (width != nullptr) *width = surface->w;
    if (height != nullptr) *height = surface->h;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(context->renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void amstDrawButton(AmstContext* AMST_NONNULL context, AmstButton* AMST_NONNULL button) {
    defsAssert(gInitialized);

    int32_t textWidth, textHeight;
    amstGetTextMetrics(context, button->text, &textWidth, &textHeight);

    const bool mouseHovered =
        context->mouseX >= button->x && context->mouseX <= textWidth + 5 &&
        context->mouseY >= button->y && context->mouseY <= textHeight + 5;

    SDL_Color color = mouseHovered ? ((SDL_Color) {127, 127, 127, 127}) : ((SDL_Color) {255, 255, 255, 255});

    SDL_Texture* texture = renderText(context, button->text, color, nullptr, nullptr);

    SDL_RenderCopy(
        context->renderer,
        texture,
        nullptr,
        &((SDL_Rect) {button->x + 5, button->y + 5, textWidth, textHeight})
    );
    SDL_DestroyTexture(texture);

    uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(context->renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(context->renderer, &((SDL_Rect) {button->x, button->y, textWidth + 5, textHeight + 5}));
    SDL_SetRenderDrawColor(context->renderer, r, g, b, a);

    if (context->mouseDown) {
        context->mouseDown = false;
        button->clickHandler();
    }
}
