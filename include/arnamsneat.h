
#pragma once

#include <SDL2/SDL.h>

#ifndef __GNUC__
#   error
#endif

#define ARNAMSNEAT_API [[gnu::visibility("default")]]

ARNAMSNEAT_API bool arnamsneatInit(void);
ARNAMSNEAT_API extern bool arnamsneatQuit(void);
