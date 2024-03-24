/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "arnamsneat.h"
#include "defs.h"
#include <stdint.h>

struct _AmstContext {
    int32_t windowWidth, windowHeight, rendererWidth, rendererHeight;
    float scaleX, scaleY;
};

static defsAtomic bool gInitialized = false;

void amstInit(void) {
    if (gInitialized) return;
    gInitialized = true;
}

void amstSetSdlRendererHints(void) {
    defsAssert(gInitialized);
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "3"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"));
}

AmstContext* AMST_NULLABLE amstContextCreate(SDL_Window* AMST_NONNULL window) {
    defsAssert(gInitialized);
    DEFS_USED(window);
    return (void*) 0x1;
}

void amstProcessEvents(void) {
    defsAssert(gInitialized);
}

void amstContextDestroy(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    DEFS_USED(context);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}
