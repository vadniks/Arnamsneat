
#pragma once

#include <SDL2/SDL.h>

#if !defined(__GNUC__) || __STDC_VERSION__ < 202000L
#   error
#endif

#define ARNAMSNEAT_API [[gnu::visibility("default")]]

ARNAMSNEAT_API bool arnamsneatInit(void);
ARNAMSNEAT_API bool arnamsneatQuit(void);
