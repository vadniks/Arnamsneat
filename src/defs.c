
#include "defs.h"

#include <stdlib.h>
#include <SDL2/SDL.h>

void defsAssert(bool condition) { if (!condition) abort(); }
bool defsSuccessful(int result) { return result == 0; }

void* AMST_NONNULL defsMalloc(size_t size) {
    void* const pointer = SDL_malloc(size);
    defsAssert(pointer != nullptr);
    return pointer;
}

void* AMST_NONNULL defsRealloc(void* AMST_NULLABLE memory, size_t size) {
    void* const pointer = SDL_realloc(memory, size);
    defsAssert(pointer != nullptr);
    return pointer;
}

void defsFree(void* AMST_NULLABLE memory) { SDL_free(memory); }
