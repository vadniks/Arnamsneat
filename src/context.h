/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <arnamsneat/arnamsneat.h>

struct _AmstContext {
    SDL_Window* AMST_NONNULL window;
    SDL_Renderer* AMST_NONNULL renderer;
    int32_t windowWidth, windowHeight, rendererWidth, rendererHeight, currentWidth, currentHeight;
    float scaleX, scaleY;
    TTF_Font* AMST_NONNULL font;
    int32_t mouseX, mouseY;
    bool mouseDown;
    int32_t lastDrawnWidth;
    int32_t lastDrawnHeight;
    bool keyboardInputting;
    bool keyboardInputErasing;
    int32_t nextGlyph;
    const void* AMST_NULLABLE activeField;
};
