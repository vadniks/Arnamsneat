
#pragma once

#include "arnamsneatPrivate.h"
#include <SDL2/SDL.h>

#if !defined(__GNUC__) || !defined(__STDC__) || __STDC_VERSION__ < 202000L
#   error
#endif

#define AMST_EXPORT [[gnu::visibility("default")]]

struct AMST_EXPORT _AmstContext;
typedef struct _AmstContext AmstContext;

AMST_EXPORT
void amstInit(void);

AMST_EXPORT
void amstSetSdlRendererHints(void);

AMST_EXPORT
AmstContext* AMST_NULLABLE amstContextCreate(SDL_Window* AMST_NONNULL window);

AMST_EXPORT
void amstProcessEvents(void);

AMST_EXPORT
void amstContextDestroy(AmstContext* AMST_NONNULL context);

AMST_EXPORT
void amstQuit(void);
