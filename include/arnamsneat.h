
#pragma once

#include <SDL2/SDL.h>

#if !defined(__GNUC__) || !defined(__STDC__) || __STDC_VERSION__ < 202000L
#   error
#endif

#define AMST_EXPORT [[gnu::visibility("default")]]
#define AMST_NONNULL(...) [[gnu::nonnull(__VA_ARGS__)]]
#define AMST_RETURNS_NONNULL [[gnu::returns_nonnull]]

struct _AmstRenderer;
typedef struct _AmstRenderer AmstRenderer;

AMST_EXPORT
void amstInit(void);

AMST_EXPORT
AMST_NONNULL() AMST_RETURNS_NONNULL
AmstRenderer* amstCreateRenderer(SDL_Window* window);

AMST_EXPORT
void amstProcessEvents(void);

AMST_EXPORT
AMST_NONNULL()
void amstDestroyRenderer(SDL_Window* window);

AMST_EXPORT
void amstQuit(void);
