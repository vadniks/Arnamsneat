/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <arnamsneat/text.h>
#include <arnamsneat/image.h>
#include "defs.h"
#include "context.h"
#include "internal.h"

void amstGetTextMetrics(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);
    TTF_SizeUTF8(context->font, text, width, height);
}

void amstText(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    SDL_Color color,
    int32_t x,
    int32_t y
) {
    defsAssert(gInitialized);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(context->font, text, color);

    amstImage(context, surface, x, y);

    context->lastWidth = surface->w;
    context->lastHeight = surface->h;

    SDL_FreeSurface(surface);
}
