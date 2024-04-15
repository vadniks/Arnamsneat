/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <arnamsneat/field.h>
#include <arnamsneat/text.h>
#include "internal.h"
#include "context.h"
#include "defs.h"

struct AmstFieldState {
    bool active;
    char* AMST_NULLABLE input;
    int32_t length;
};

void amstGetFieldMetrics(
    int32_t textWidth,
    int32_t textHeight,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);
}

AmstFieldState* AMST_NONNULL amstCreateFieldState(void) {
    AmstFieldState* state = defsMalloc(sizeof *state);
    state->active = false;
    state->input = nullptr;
    state->length = 0;
    return state;
}

void amstDestroyFieldState(AmstFieldState* AMST_NONNULL state) {
    defsFree(state->input);
    defsAssert(state);
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
        amstGetTextMetrics(context, state->input, &labelWidth, &labelHeight);
    else {
        textWidth = 0;
        textHeight = 0;
    }

    const int32_t
        width = defsMax(probeWidth, labelWidth),
        height = probeHeight;

    const bool mouseHovered =
        context->mouseX >= x && context->mouseX <= x + width &&
        context->mouseY >= y && context->mouseY <= y + height;

    if (mouseHovered && context->mouseDown) {
        context->mouseDown = false;
        context->activeField = state;
    }


}
