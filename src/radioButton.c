/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <arnamsneat/core.h>
#include <arnamsneat/radioButon.h>
#include <arnamsneat/text.h>
#include "internal.h"
#include "context.h"
#include "defs.h"

void amstGetRadioButtonMetrics(
    int32_t textWidth,
    int32_t textHeight,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);
    const int32_t radius = 15;

    *width = radius * 2 + 5 + textWidth;
    *height = defsMax(radius, textHeight);
}

static void drawCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius) { // Midpoint Circle Algorithm
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

        if (error <= 0) {
            y++;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            x--;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void amstRadioButton(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    int32_t x,
    int32_t y,
    bool checked,
    void (* AMST_NONNULL clickHandler)(void)
) {
    defsAssert(gInitialized);
    const int32_t radius = 15;

    int32_t textWidth, textHeight;
    amstGetTextMetrics(context, text, &textWidth, &textHeight);

    context->lastDrawnWidth = radius * 2 + 5 + textWidth;
    context->lastDrawnHeight = defsMax(radius, textHeight);

    const bool mouseHovered =
        context->mouseX >= x && context->mouseX <= x + radius * 2 &&
        context->mouseY >= y && context->mouseY <= y + context->lastDrawnHeight;

    if (mouseHovered && context->mouseDown) {
        context->mouseDown = false;
        clickHandler();
    }

    uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(context->renderer, &r, &g, &b, &a);
    const SDL_Color color = amstMakeColor(mouseHovered ? amstHoverColor : amstForegroundColor);
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);

    for (int32_t i = radius; i >= (checked ? 0 : radius); i--)
        drawCircle(context->renderer, x + radius, y + textHeight / 2, i);

    SDL_SetRenderDrawColor(context->renderer, r, g, b, a);

    amstText(context, text, amstForegroundColor, x + radius * 2 + 5, y);
}
