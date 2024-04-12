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
void amstInit(void);

AMST_EXPORT
bool amstInitialized(void);

AMST_EXPORT
void amstSetSdlRendererHints(void);

AMST_EXPORT
    AmstContext* AMST_NULLABLE amstContextCreate(
    SDL_Window* AMST_NONNULL window,
    SDL_Renderer* AMST_NONNULL renderer,
    TTF_Font* AMST_NONNULL font
);

AMST_EXPORT
void amstProcessEvent(AmstContext* AMST_NONNULL context, SDL_Event* AMST_NONNULL event);

AMST_EXPORT
void amstPrepareToDraw(AmstContext* AMST_NONNULL context);

AMST_EXPORT
void amstDrawAll(AmstContext* AMST_NONNULL context);

AMST_EXPORT
void amstGetCurrentSizes(AmstContext* AMST_NONNULL context, int32_t* AMST_NONNULL width, int32_t* AMST_NONNULL height);

AMST_EXPORT
void amstGetLastDrawnSizes(AmstContext* AMST_NONNULL context, int32_t* AMST_NONNULL width, int32_t* AMST_NONNULL height);

AMST_EXPORT
void amstContextDestroy(AmstContext* AMST_NONNULL context);

AMST_EXPORT
void amstQuit(void);
