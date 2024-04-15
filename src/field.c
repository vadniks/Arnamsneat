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
    char* AMST_NULLABLE input;
    int32_t length;
};

AmstFieldState* AMST_NONNULL amstCreateFieldState(void) {
    AmstFieldState* state = defsMalloc(sizeof *state);
    state->input = nullptr;
    state->length = 0;
    return state;
}

void amstDestroyFieldState(AmstFieldState* AMST_NONNULL state) {
    defsFree(state->input);
    defsFree(state);
}

void amstField(
    AmstContext* AMST_NONNULL context,
    int32_t x,
    int32_t y,
    const char* AMST_NONNULL label,
    AmstFieldState* AMST_NONNULL state,
    void (* AMST_NONNULL inputHandler)(const char* AMST_NONNULL)
) {
    defsAssert(gInitialized);

    int32_t probeWidth, probeHeight;
    amstGetTextMetrics(context, "A", &probeWidth, &probeHeight);

    int32_t labelWidth, labelHeight;
    amstGetTextMetrics(context, label, &labelWidth, &labelHeight);

    int32_t textWidth, textHeight;
    if (state->input != nullptr)
        amstGetTextMetrics(context, state->input, &textWidth, &textHeight);
    else {
        textWidth = 0;
        textHeight = 0;
    }

    const int32_t
        width = defsMax(probeWidth, labelWidth),
        height = probeHeight;

    const bool mouseHovered =
        context->mouseX >= x && context->mouseX <= x + width + 10 &&
        context->mouseY >= y && context->mouseY <= y + height + 10;

    if (mouseHovered && context->mouseDown) {
        context->mouseDown = false;
        context->activeField = state;
    }

    if (context->activeField == state) {
        if (context->keyboardInputErasing && state->length > 0) {
            context->keyboardInputErasing = false;
            state->length--;
            state->input[state->length] = 0;
            // no realloc to shrink the memory region's size 'cause it'll get freed anyway afterward
        }

        if (context->keyboardInputting && textWidth < width) {
            context->keyboardInputting = false;

            state->input = defsRealloc(state->input, state->length + 2);
            state->input[state->length] = (context->keyboardInput + context->keyboardInputSize - 1)[0];
            state->input[state->length + 1] = 0;
            state->length++;

            inputHandler(state->input);
        }
    }

    if (state->input != nullptr && state->length > 0)
        amstText(context, state->input, amstForegroundColor, x + 5, y + 5);
    else
        amstText(
            context,
            label,
            mouseHovered ? amstHoverColor : amstSecondaryColor,
            x + 5,
            y + 5
        );

    SDL_Color color = amstMakeColor(mouseHovered ? amstHoverColor : amstForegroundColor);

    uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(context->renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLine(context->renderer, x, y + height + 10, x + width + 10, y + height + 10);
    SDL_SetRenderDrawColor(context->renderer, r, g, b, a);

    context->lastDrawnWidth = width + 10;
    context->lastDrawnHeight = height + 10;
}

const char* AMST_NULLABLE amstFieldText(AmstFieldState* AMST_NONNULL state) {
    defsAssert(gInitialized);
    return state->input;
}
