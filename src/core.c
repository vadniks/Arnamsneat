
#include <arnamsneat/core.h>
#include "internal.h"
#include "context.h"
#include "defs.h"

void amstInit(void) {
    if (gInitialized) return;
    gInitialized = true;
}

bool amstInitialized(void) { return gInitialized; }

void amstSetSdlRendererHints(void) {
    defsAssert(gInitialized);
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "3"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1"));
    defsAssert(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"));
}

static void updateSizes(AmstContext* AMST_NONNULL context) {
    SDL_GetWindowSize(context->window, &(context->windowWidth), &(context->windowHeight));
    SDL_GetRendererOutputSize(context->renderer, &(context->rendererWidth), &(context->rendererHeight));

    context->scaleX = (float) context->rendererWidth / (float) context->windowWidth;
    context->scaleY = (float) context->rendererHeight / (float) context->windowHeight;

    SDL_RenderSetScale(context->renderer, context->scaleX, context->scaleY);
}

AmstContext* AMST_NULLABLE amstContextCreate(
    SDL_Window* AMST_NONNULL window,
    SDL_Renderer* AMST_NONNULL renderer,
    TTF_Font* AMST_NONNULL font
) {
    defsAssert(gInitialized);

    AmstContext* context = defsMalloc(sizeof *context);
    context->window = window;
    context->renderer = renderer;
    context->font = font;
    updateSizes(context);

    return context;
}

void amstProcessEvent(AmstContext* AMST_NONNULL context, SDL_Event* AMST_NONNULL event) {
    defsAssert(gInitialized);

    switch (event->type) {
        case SDL_MOUSEMOTION:
            context->mouseX = event->motion.x;
            context->mouseY = event->motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            context->mouseDown = true;
            break;
        case SDL_MOUSEBUTTONUP:
            context->mouseDown = false;
            break;
    }

    DEFS_USED(event);
}

void amstPrepareToDraw(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    SDL_GetWindowSizeInPixels(context->window, &(context->currentWidth), &(context->currentHeight));
    SDL_SetRenderDrawColor(context->renderer, 50, 50, 50, 255);
    SDL_RenderClear(context->renderer);
}

void amstDrawAll(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    SDL_RenderPresent(context->renderer);
}

void amstGetCurrentSizes(AmstContext* AMST_NONNULL context, int32_t* AMST_NONNULL width, int32_t* AMST_NONNULL height) {
    defsAssert(gInitialized);
    *width = context->currentWidth;
    *height = context->currentHeight;
}

void amstContextDestroy(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    defsFree(context);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}
