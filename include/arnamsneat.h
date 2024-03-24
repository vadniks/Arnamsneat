
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

struct _AmstRenderer;
typedef struct _AmstRenderer AmstRenderer;

AMST_EXPORT
void amstInit(void);

AMST_EXPORT
AmstRenderer* AMST_NULLABLE amstCreateRenderer(SDL_Window* AMST_NONNULL window);

AMST_EXPORT
void amstProcessEvents(void);

AMST_EXPORT
void amstDestroyRenderer(SDL_Window* AMST_NONNULL window);

AMST_EXPORT
void amstQuit(void);
