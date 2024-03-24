
#pragma once

#include <SDL2/SDL.h>

#if !defined(__GNUC__) || !defined(__STDC__) || __STDC_VERSION__ < 202000L
#   error
#endif

#define AMST_EXPORT [[gnu::visibility("default")]]

#ifdef __clang__
#   define AMST_NULLABLE _Nullable
#   define AMST_NONNULL _Nonnull
#else
#   define AMST_NULLABLE
#   define AMST_NONNULL
#endif

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
