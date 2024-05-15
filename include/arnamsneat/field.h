/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <arnamsneat/arnamsneat.h>

struct AMST_EXPORT AmstFieldState;
typedef struct AmstFieldState AmstFieldState;

AMST_EXPORT
AmstFieldState* AMST_NONNULL amstCreateFieldState(void);

AMST_EXPORT
void amstDestroyFieldState(AmstFieldState* AMST_NONNULL state);

AMST_EXPORT
void amstGetFieldMetrics(
    AmstContext* AMST_NONNULL context,
    int32_t labelWidth,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
);

AMST_EXPORT
void amstField(
    AmstContext* AMST_NONNULL context,
    int32_t x,
    int32_t y,
    const char* AMST_NONNULL label,
    AmstFieldState* AMST_NONNULL state
);

AMST_EXPORT
char* AMST_NULLABLE amstFieldText(AmstFieldState* AMST_NONNULL state);
