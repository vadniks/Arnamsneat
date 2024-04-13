/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <arnamsneat/checkbox.h>
#include <arnamsneat/text.h>
#include "internal.h"
#include "context.h"
#include "defs.h"

void amstGetCheckboxMetrics(
    int32_t textWidth,
    int32_t textHeight,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);
    *width = textWidth + 5 + textWidth;
    *height = textHeight + 10;
}

void amstCheckbox(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    int32_t x,
    int32_t y,
    bool checked,
    void (* AMST_NONNULL clickHandler)(void)
) {
    defsAssert(gInitialized);

    int32_t textWidth, textHeight;
    amstGetTextMetrics(context, text, &textWidth, &textHeight);
    const int32_t boxSize = textHeight;

    const bool mouseHovered =
        context->mouseX >= x && context->mouseX <= x + boxSize &&
        context->mouseY >= y && context->mouseY <= y + boxSize;

    const bool mouseClicked = mouseHovered && context->mouseDown;

    const SDL_Color textColor = {255, 255, 255, 255};

    const SDL_Color boxColor =
        mouseClicked
        ? ((SDL_Color) {50, 50, 50, 50})
        : mouseHovered
            ? ((SDL_Color) {127, 127, 127, 127})
            : textColor;

    amstText(context, text, textColor, x + boxSize + 5, y + 5);

    uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(context->renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(context->renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);

    const SDL_Rect rect = {x, y + 5, boxSize, boxSize};
    SDL_RenderDrawRect(context->renderer, &rect);
    if (checked) SDL_RenderFillRect(context->renderer, &rect);
    SDL_SetRenderDrawColor(context->renderer, r, g, b, a);

    context->lastDrawnWidth = boxSize + 5 + textWidth;
    context->lastDrawnHeight = boxSize + 10;

    if (mouseClicked) {
        context->mouseDown = false;
        clickHandler();
    }
}
