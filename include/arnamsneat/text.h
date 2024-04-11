
#pragma once

#include <arnamsneat/arnamsneat.h>

AMST_EXPORT
void amstGetTextMetrics(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
);

AMST_EXPORT
void amstText(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    SDL_Color color,
    int32_t x,
    int32_t y
);
