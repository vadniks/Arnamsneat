/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <arnamsneat/core.h>
#include <arnamsneat/infiiteProgressbar.h>
#include <arnamsneat/text.h>
#include "internal.h"
#include "context.h"
#include "defs.h"

typedef enum {
    STATE_A = 150,
    STATE_B = 300,
    STATE_C = 450,
    STATE_D = 600,
    STATE_E = 750,
    STATE_F = 1000
} State;

void amstGetInfiniteProgressbarMetrics(
    AmstContext* AMST_NONNULL context,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);
    amstGetTextMetrics(context, "==----------", width, height);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "Simplify"
void amstInfiniteProgressbar(AmstContext* AMST_NONNULL context, int32_t x, int32_t y) {
    defsAssert(gInitialized);
    const uint32_t interval = SDL_GetTicks() % STATE_F;

    const char* string;
    if (STATE_A >= interval && interval <= STATE_B)
        string = "==----------";
    else if (STATE_B >= interval && interval <= STATE_C)
        string = "--==--------";
    else if (STATE_C >= interval && interval <= STATE_D)
        string = "----==------";
    else if (STATE_D >= interval && interval <= STATE_E)
        string = "------==----";
    else if (STATE_E >= interval && interval <= STATE_F)
        string = "--------==--";
    else if (STATE_F >= interval)
        string = "----------==";
    amstText(context, string, amstActiveColor, x, y);

    // last drawn
}
#pragma clang diagnostic pop
