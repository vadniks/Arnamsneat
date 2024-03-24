
#include "arnamsneat.h"
#include "defs.h"

static ATOMIC bool gInitialized = false;

bool arnamsneatInit(uint32_t flags) {
    if (gInitialized) return false;

    if (!defsSuccessful(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | flags)))
        return false;


    gInitialized = true;
    return true;
}

bool arnamsneatProcessEvents(void) {
    defsAssert(gInitialized);
    return false;
}

bool arnamsneatQuit(void) {
    if (!gInitialized) return false;
    return true;
}
