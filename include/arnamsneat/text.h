
#pragma once

#include <arnamsneat/arnamsneat.h>

AMST_EXPORT
void amstGetTextMetrics(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
);

SDL_Texture* AMST_NONNULL renderText(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    SDL_Color color,
    int32_t* AMST_NULLABLE width,
    int32_t* AMST_NULLABLE height
);
