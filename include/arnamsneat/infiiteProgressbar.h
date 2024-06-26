/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <arnamsneat/arnamsneat.h>

AMST_EXPORT
void amstGetInfiniteProgressbarMetrics(
    AmstContext* AMST_NONNULL context,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
);

AMST_EXPORT
void amstInfiniteProgressbar(AmstContext* AMST_NONNULL context, int32_t x, int32_t y);
