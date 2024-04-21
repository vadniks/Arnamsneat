/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#if !defined(__GNUC__) || !defined(__STDC__) || __STDC_VERSION__ < 202000L // C23
#   error
#endif

#define AMST_EXPORT [[gnu::visibility("default")]]

#ifdef __clang__
#   define AMST_NULLABLE _Nullable
#   define AMST_NONNULL _Nonnull
#else
#   define AMST_NULLABLE
#   define AMST_NONNULL
#endif

static_assert(sizeof(char) == 1);

struct AMST_EXPORT _AmstContext;
typedef struct _AmstContext AmstContext;
