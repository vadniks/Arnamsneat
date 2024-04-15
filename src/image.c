/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <arnamsneat/image.h>
#include "defs.h"
#include "context.h"
#include "internal.h"

void amstImage(
    AmstContext* AMST_NONNULL context,
    SDL_Surface* AMST_NONNULL surface,
    int32_t x,
    int32_t y
) {
    defsAssert(gInitialized);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(context->renderer, surface);
    defsAssert(texture != nullptr);

    SDL_RenderCopy(
        context->renderer,
        texture,
        nullptr,
        &((SDL_Rect) {x, y, surface->w, surface->h})
    );

    SDL_DestroyTexture(texture);
}
