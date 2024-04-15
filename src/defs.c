/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

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
    defsAssert((size > 0 && pointer != nullptr) || size == 0);
    return pointer;
}

void defsFree(void* AMST_NULLABLE memory) { SDL_free(memory); }

int32_t defsMax(int32_t a, int32_t b) { return a > b ? a : b; }

int32_t defsMin(int32_t a, int32_t b) { return a < b ? a : b; }
