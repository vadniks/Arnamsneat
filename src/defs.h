
#pragma once

#define defsAtomic _Atomic
#define DEFS_USED(x) ((void) x)

void defsAssert(bool condition);
bool defsSuccessful(int result);
