
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

void amstText(
    AmstContext* AMST_NONNULL context,
    const char* AMST_NONNULL text,
    SDL_Color color,
    int32_t x,
    int32_t y
) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(context->font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(context->renderer, surface);

    SDL_RenderCopy(
        context->renderer,
        texture,
        nullptr,
        &((SDL_Rect) {x, y, surface->w, surface->h})
    );
    SDL_DestroyTexture(texture);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
