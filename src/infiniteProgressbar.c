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

void amstInfiniteProgressbar(AmstContext* AMST_NONNULL context, int32_t x, int32_t y) {
    defsAssert(gInitialized);
    const uint32_t interval = SDL_GetTicks() % STATE_F;

    const char* string;

    if (STATE_A >= interval)
        string = "==----------";
    else if (STATE_B >= interval)
        string = "--==--------";
    else if (STATE_C >= interval)
        string = "----==------";
    else if (STATE_D >= interval)
        string = "------==----";
    else if (STATE_E >= interval)
        string = "--------==--";
    else if (STATE_F >= interval)
        string = "----------==";

    amstText(context, string, amstActiveColor, x, y);

    int32_t width, height;
    amstGetInfiniteProgressbarMetrics(context, &width, &height);
    context->lastDrawnWidth = width;
    context->lastDrawnHeight = height;
}
