
#pragma once

#include "../include/arnamsneatPrivate.h"
#include <stddef.h>

#define defsAtomic _Atomic
#define DEFS_USED(x) ((void) x)

void defsAssert(bool condition);
bool defsSuccessful(int result);
void* AMST_NONNULL defsMalloc(size_t size);
void* AMST_NONNULL defsRealloc(void* AMST_NULLABLE memory, size_t size);
void defsFree(void* AMST_NULLABLE memory);
