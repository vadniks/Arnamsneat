/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <arnamsneat/core.h>
#include <arnamsneat/field.h>
#include <arnamsneat/text.h>
#include "internal.h"
#include "context.h"
#include "defs.h"

struct AmstFieldState {
    int32_t* AMST_NULLABLE glyphs;
    int32_t length;
};

AmstFieldState* AMST_NONNULL amstCreateFieldState(void) {
    defsAssert(gInitialized);
    AmstFieldState* state = defsMalloc(sizeof *state);
    state->glyphs = nullptr;
    state->length = 0;
    return state;
}

void amstDestroyFieldState(AmstFieldState* AMST_NONNULL state) {
    defsAssert(gInitialized);
    defsFree(state->glyphs);
    defsFree(state);
}

void amstGetFieldMetrics(
    AmstContext* AMST_NONNULL context,
    int32_t labelWidth,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);

    int32_t probeWidth, probeHeight;
    amstGetTextMetrics(context, "A", &probeWidth, &probeHeight);

    *width = defsMax(probeWidth, labelWidth) + 10;
    *height = probeHeight + 10;
}

void amstField(
    AmstContext* AMST_NONNULL context,
    int32_t x,
    int32_t y,
    const char* AMST_NONNULL label,
    AmstFieldState* AMST_NONNULL state
) {
    defsAssert(gInitialized);

    int32_t probeWidth, probeHeight;
    amstGetTextMetrics(context, "A", &probeWidth, &probeHeight);

    int32_t labelWidth, labelHeight;
    amstGetTextMetrics(context, label, &labelWidth, &labelHeight);

    int32_t textWidth;
    if (state->glyphs != nullptr) {
        textWidth = 0;
        for (int32_t i = 0; i < state->length; i++) {
            char glyph[sizeof(int32_t) + 1] = {0};
            *((int32_t*) glyph) = state->glyphs[i];

            int32_t w, h;
            amstGetTextMetrics(context, glyph, &w, &h);
            textWidth += w;
        }
    } else
        textWidth = 0;

    const int32_t
        width = defsMax(probeWidth, labelWidth),
        height = probeHeight;

    const bool mouseHovered =
        context->mouseX >= x && context->mouseX <= x + width + 10 &&
        context->mouseY >= y && context->mouseY <= y + height + 10;

    const bool active = context->activeField == state;

    if (mouseHovered && context->mouseDown) {
        context->mouseDown = false;
        context->activeField = state;
    }

    if (active) {
        if (context->keyboardInputErasing && state->length > 0) {
            context->keyboardInputErasing = false;
            state->length--;
            // no realloc to shrink the memory region's size 'cause it'll get freed anyway afterward
        }

        if (context->keyboardInputting && textWidth < width) {
            context->keyboardInputting = false;
            state->glyphs = defsRealloc(state->glyphs, ++(state->length) * sizeof(int32_t));
            defsAssert(state->glyphs != nullptr);
            state->glyphs[state->length - 1] = context->nextGlyph;
        }
    }

    if (state->length > 0) {
        int32_t totalWidth = 0;
        for (int32_t i = 0; i < state->length; i++) {
            char glyph[sizeof(int32_t) + 1] = {0};
            *((int32_t*) glyph) = state->glyphs[i];

            int32_t w, h;
            amstGetTextMetrics(context, glyph, &w, &h);

            amstText(context, glyph, amstForegroundColor, x + 5 + totalWidth, y + 5);
            totalWidth += w;
        }
    } else
        amstText(
            context,
            label,
            mouseHovered ? amstHoverColor : amstSecondaryColor,
            x + 5,
            y + 5
        );

    SDL_Color color = amstMakeColor(
        mouseHovered
            ? amstHoverColor
            : active
                ? amstActiveColor
                : amstForegroundColor
    );

    uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(context->renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLine(context->renderer, x, y + height + 10, x + width + 10, y + height + 10);
    SDL_SetRenderDrawColor(context->renderer, r, g, b, a);

    context->lastDrawnWidth = width + 10;
    context->lastDrawnHeight = height + 10;
}

char* AMST_NULLABLE amstFieldText(AmstFieldState* AMST_NONNULL state) {
    defsAssert(gInitialized);

    char* text = nullptr;
    int32_t textSize = 0;

    for (int32_t i = 0; i < state->length; i++) {
        const char* glyphChars = (char*) &(state->glyphs[i]);

        for (int32_t j = 0; j < (int32_t) sizeof(int32_t); j++) {
            if (glyphChars[j] == 0) break;
            text = defsRealloc(text, ++textSize);
            text[textSize - 1] = glyphChars[j];
        }
    }

    text = defsRealloc(text, ++textSize);
    text[textSize - 1] = 0;

    return text;
}
