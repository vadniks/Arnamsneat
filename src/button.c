/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <arnamsneat/button.h>
#include <arnamsneat/text.h>
#include "internal.h"
#include "context.h"
#include "defs.h"

void amstGetButtonMetrics(
    int32_t textWidth,
    int32_t textHeight,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);
    *width = textWidth + 10;
    *height = textHeight + 10;
}

void amstButton(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    int32_t x,
    int32_t y,
    void (* AMST_NONNULL clickHandler)(void)
) {
    defsAssert(gInitialized);

    int32_t textWidth, textHeight;
    amstGetTextMetrics(context, text, &textWidth, &textHeight);

    const bool mouseHovered =
        context->mouseX >= x && context->mouseX <= x + textWidth + 10 &&
        context->mouseY >= y && context->mouseY <= y + textHeight + 10;

    const bool mouseClicked = mouseHovered && context->mouseDown;

    SDL_Color color =
        mouseClicked
        ? ((SDL_Color) {50, 50, 50, 50})
        : mouseHovered
            ? ((SDL_Color) {127, 127, 127, 127})
            : ((SDL_Color) {255, 255, 255, 255});

    amstText(context, text, color, x + 5, y + 5);

    uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(context->renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(context->renderer, &((SDL_Rect) {x, y, textWidth + 10, textHeight + 10}));
    SDL_SetRenderDrawColor(context->renderer, r, g, b, a);

    if (mouseClicked) {
        context->mouseDown = false;
        clickHandler();
    }
}
