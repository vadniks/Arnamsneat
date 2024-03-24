
#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

#if !defined(__GNUC__) || !defined(__STDC__) || __STDC_VERSION__ < 202000L
#   error
#endif

#define ARNAMSNEAT_API [[gnu::visibility("default")]]

ARNAMSNEAT_API bool arnamsneatInit(uint32_t flags);
ARNAMSNEAT_API bool arnamsneatProcessEvents(void);
ARNAMSNEAT_API bool arnamsneatQuit(void);
