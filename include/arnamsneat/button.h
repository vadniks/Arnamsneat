
#pragma once

#include <arnamsneat/arnamsneat.h>

AMST_EXPORT
void amstGetButtonMetrics(
    int32_t textWidth,
    int32_t textHeight,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
);

AMST_EXPORT
void amstButton(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    int32_t x,
    int32_t y,
    void (* AMST_NONNULL clickHandler)(void)
);
