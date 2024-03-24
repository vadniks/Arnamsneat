
#pragma once

#include <SDL2/SDL.h>

#if !defined(__GNUC__) || !defined(__STDC__) || __STDC_VERSION__ < 202000L
#   error
#endif

#define ARNAMSNEAT_EXPORT [[gnu::visibility("default")]]
#define ARNAMSNEAT_NONNULL(...) [[gnu::nonnull(__VA_ARGS__)]]
#define ARNAMSNEAT_RETURNS_NONNULL [[gnu::returns_nonnull]]

struct _ArnamsneatRenderer;
typedef struct _ArnamsneatRenderer ArnamsneatRenderer;

ARNAMSNEAT_EXPORT
void arnamsneatInit(void);

ARNAMSNEAT_EXPORT
ARNAMSNEAT_NONNULL() ARNAMSNEAT_RETURNS_NONNULL
ArnamsneatRenderer* arnamsneatCreateRenderer(SDL_Window* window);

ARNAMSNEAT_EXPORT
void arnamsneatProcessEvents(void);

ARNAMSNEAT_EXPORT
ARNAMSNEAT_NONNULL()
void arnamsneatDestroyRenderer(SDL_Window* window);

ARNAMSNEAT_EXPORT
void arnamsneatQuit(void);
