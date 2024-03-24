
#include "arnamsneat.h"
#include "defs.h"

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
