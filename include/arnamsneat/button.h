
#pragma once

#include <arnamsneat/arnamsneat.h>

typedef struct {
    const char* AMST_NONNULL text; // utf-8
    int32_t x, y;
    void (* AMST_NONNULL clickHandler)(void);
} AmstButton;

AMST_EXPORT
void amstGetButtonMetrics(
    int32_t textWidth,
    int32_t textHeight,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
);

AMST_EXPORT
void amstDrawButton(AmstContext* AMST_NONNULL context, AmstButton* AMST_NONNULL button);
