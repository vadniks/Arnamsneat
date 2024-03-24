
#include "arnamsneat.h"
#include "defs.h"
#include <assert.h>

static ATOMIC bool gInitialized = false;

bool arnamsneatInit(void) {
    if (gInitialized) return false;
    if (!defsSdlSuccessful(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)))
        return false;

    gInitialized = true;
    return true;
}

bool arnamsneatProcessEvents(void) {
    assert(gInitialized);
    return false;
}

bool arnamsneatQuit(void) {
    if (!gInitialized) return false;
    return true;
}
