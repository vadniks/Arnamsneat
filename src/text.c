
#include <arnamsneat/text.h>
#include "defs.h"
#include "context.h"
#include "internal.h"

void amstGetTextMetrics(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    defsAssert(gInitialized);
    TTF_SizeUTF8(context->font, text, width, height);
}

SDL_Texture* AMST_NONNULL renderText(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    SDL_Color color,
    int32_t* AMST_NULLABLE width,
    int32_t* AMST_NULLABLE height
) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(context->font, text, color);

    if (width != nullptr) *width = surface->w;
    if (height != nullptr) *height = surface->h;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(context->renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}
