
#include "defs.h"

#include <stdlib.h>

void defsAssert(bool condition) { if (!condition) abort(); }
bool defsSuccessful(int result) { return result == 0; }
