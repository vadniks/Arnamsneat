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
    AmstFieldState* AMST_NONNULL state,
    void (* AMST_NONNULL inputHandler)(const char* AMST_NONNULL)
) {
    defsAssert(gInitialized);

    int32_t probeWidth, probeHeight;
    amstGetTextMetrics(context, "A", &probeWidth, &probeHeight);

    int32_t labelWidth, labelHeight;
    amstGetTextMetrics(context, label, &labelWidth, &labelHeight);

    if (context->keyboardInputting) {
        context->keyboardInputting = false;
        state->glyphs = defsRealloc(state->glyphs, ++(state->length) * sizeof(int32_t));
        defsAssert(state->glyphs != nullptr);
        state->glyphs[state->length - 1] = context->nextGlyph;

//        const char* nextInput = nullptr;
//        if (state->glyphs != nullptr) {
//            nextInput = (char[4]) {};
//            *((int32_t*) nextInput) = context->nextGlyph;
//        }
        SDL_Log("%d", SDL_strlen(&(context->nextGlyph)));
    }

//    char input[state->length * sizeof(int32_t)];
//    SDL_memset(input, 0, state->length);
//    for (int32_t i = 0; i < state->length; i++) {
//        int32_t glyph = state->glyphs[i];
//
//        for (int32_t j = 0; j < 4; j++)
//            input[i + j] = (char) ((glyph >> (j * 8)) & 0xff);
//    }

//    for (int32_t j = 0; j < 4; j++)
//        SDL_Log("# %c", input[j]);
//    SDL_Log("");
//    if (state->length > 0)
//        amstText(context, input, amstForegroundColor, x + 5, y + 5);





//    int32_t textWidth, textHeight;
//    if (state->glyphs != nullptr)
//        amstGetTextMetrics(context, state->input, &textWidth, &textHeight);
//    else {
//        textWidth = 0;
//        textHeight = 0;
//    }
//
//    const int32_t
//        width = defsMax(probeWidth, labelWidth),
//        height = probeHeight;
//
//    const bool mouseHovered =
//        context->mouseX >= x && context->mouseX <= x + width + 10 &&
//        context->mouseY >= y && context->mouseY <= y + height + 10;
//
//    const bool active = context->activeField == state;
//
//    if (mouseHovered && context->mouseDown) {
//        context->mouseDown = false;
//        context->activeField = state;
//    }
//
//    if (active) {
//        if (context->keyboardInputErasing && state->length > 0) {
//            context->keyboardInputErasing = false;
//            state->length--;
//            state->input[state->length] = 0;
//            // no realloc to shrink the memory region's size 'cause it'll get freed anyway afterward
//        }
//
//        if (context->keyboardInputting && textWidth < width) {
//            context->keyboardInputting = false;
//
//            state->input = defsRealloc(state->input, state->length + 2);
//            state->input[state->length] = (context->keyboardInput + context->keyboardInputSize - 1)[0];
//            state->input[state->length + 1] = 0;
//            state->length++;
//
//            inputHandler(state->input);
//        }
//    }
//
//    if (state->input != nullptr && state->length > 0)
//        amstText(context, state->input, amstForegroundColor, x + 5, y + 5);
//    else
//        amstText(
//            context,
//            label,
//            mouseHovered ? amstHoverColor : amstSecondaryColor,
//            x + 5,
//            y + 5
//        );
//
//    SDL_Color color = amstMakeColor(
//        mouseHovered
//            ? amstHoverColor
//            : active
//                ? amstActiveColor
//                : amstForegroundColor
//    );
//
//    uint8_t r, g, b, a;
//    SDL_GetRenderDrawColor(context->renderer, &r, &g, &b, &a);
//    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
//
//    SDL_RenderDrawLine(context->renderer, x, y + height + 10, x + width + 10, y + height + 10);
//    SDL_SetRenderDrawColor(context->renderer, r, g, b, a);
//
//    context->lastDrawnWidth = width + 10;
//    context->lastDrawnHeight = height + 10;
}

const char* AMST_NULLABLE amstFieldText(AmstFieldState* AMST_NONNULL state) {
    defsAssert(gInitialized);
    return nullptr; //state->input;
}
