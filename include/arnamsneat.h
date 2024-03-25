/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include "arnamsneatPrivate.h"
#include <stdint.h>
#include <uchar.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#if !defined(__GNUC__) || !defined(__STDC__) || __STDC_VERSION__ < 202000L // C23
#   error
#endif

#define AMST_EXPORT [[gnu::visibility("default")]]

struct AMST_EXPORT _AmstContext;
typedef struct _AmstContext AmstContext;

typedef struct {
    const char16_t* AMST_NONNULL text;
    int32_t textSize;
    int32_t x, y;
} AmstButton;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMST_EXPORT
void amstInit(void);

AMST_EXPORT
void amstSetGLAttributes(void);

AMST_EXPORT
void amstSetSdlRendererHints(void);

AMST_EXPORT
AmstContext* AMST_NULLABLE amstContextCreate(
    SDL_Window* AMST_NONNULL window,
    SDL_Renderer* AMST_NONNULL renderer,
    TTF_Font* AMST_NONNULL font
);

AMST_EXPORT
void amstProcessEvent(SDL_Event* AMST_NONNULL event);

AMST_EXPORT
void amstPrepareToDraw(AmstContext* AMST_NONNULL context);

AMST_EXPORT
void amstDrawAll(AmstContext* AMST_NONNULL context);

AMST_EXPORT
void amstGetCurrentSizes(AmstContext* AMST_NONNULL context, int32_t* AMST_NONNULL width, int32_t* AMST_NONNULL height);

AMST_EXPORT
void amstContextDestroy(AmstContext* AMST_NONNULL context);

AMST_EXPORT
void amstQuit(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AMST_EXPORT
void amstGetButtonMetrics(
    AmstContext* AMST_NONNULL context,
    AmstButton* AMST_NONNULL button,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
);

AMST_EXPORT
void amstDrawButton(AmstContext* AMST_NONNULL context, AmstButton* AMST_NONNULL button);
