/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <arnamsneat/arnamsneat.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpedantic"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
typedef enum {
    AMST_BACKGROUND_COLOR = 0x25252525,
    AMST_FOREGROUND_COLOR = 0xffffffff,
    AMST_HOVER_COLOR = 0x70707070,
    AMST_ACTIVE_COLOR = 0x00ffff7f,
    AMST_SECONDARY_COLOR = 0x60606060
} AmstColor;
#pragma clang diagnostic pop

AMST_EXPORT extern uint32_t amstBackgroundColor;
AMST_EXPORT extern uint32_t amstForegroundColor;
AMST_EXPORT extern uint32_t amstHoverColor;
AMST_EXPORT extern uint32_t amstActiveColor;
AMST_EXPORT extern uint32_t amstSecondaryColor;

AMST_EXPORT
void amstInit(void);

AMST_EXPORT
bool amstInitialized(void);

AMST_EXPORT
void amstSetSdlRendererHints(void);

AMST_EXPORT
AmstContext* AMST_NULLABLE amstCreateContext(
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
SDL_Color amstMakeColor(uint32_t color);

AMST_EXPORT
void amstDestroyContext(AmstContext* AMST_NONNULL context);

AMST_EXPORT
void amstQuit(void);
