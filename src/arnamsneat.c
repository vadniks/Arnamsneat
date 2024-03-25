/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "arnamsneat.h"
#include "defs.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

struct _AmstContext {
    SDL_Window* AMST_NONNULL window;
    SDL_Renderer* AMST_NONNULL renderer;
    SDL_GLContext* AMST_NONNULL glContext;
    int32_t windowWidth, windowHeight, rendererWidth, rendererHeight, currentWidth, currentHeight;
    float scaleX, scaleY, scaleFont;
    TTF_Font* AMST_NONNULL font;
};

static defsAtomic bool gInitialized = false;

void amstInit(void) {
    if (gInitialized) return;
    gInitialized = true;
}

void amstSetGLAttributes(void) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

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
    context->scaleFont = context->scaleY;
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
    context->glContext = SDL_GL_CreateContext(window);
    context->font = font;
    updateSizes(context);

    SDL_GL_SetSwapInterval(1);
    SDL_Delay(50);

    return context;
}

void amstProcessEvent(SDL_Event* AMST_NONNULL event) {
    defsAssert(gInitialized);
    DEFS_USED(event);
}

void amstPrepareToDraw(AmstContext* AMST_NONNULL context) {
    SDL_GetWindowSizeInPixels(context->window, &(context->currentWidth), &(context->currentHeight));
    SDL_RenderClear(context->renderer);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(context->window);
}

void amstDrawAll(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    SDL_RenderPresent(context->renderer);
}

void amstGetCurrentSizes(AmstContext* AMST_NONNULL context, int32_t* AMST_NONNULL width, int32_t* AMST_NONNULL height) {
    *width = context->currentWidth;
    *height = context->currentHeight;
}

void amstContextDestroy(AmstContext* AMST_NONNULL context) {
    defsAssert(gInitialized);
    SDL_GL_DeleteContext(context->glContext);
    defsFree(context);
}

void amstQuit(void) {
    if (!gInitialized) return;
    gInitialized = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void amstGetButtonMetrics(
    AmstContext* AMST_NONNULL context,
    AmstButton* AMST_NONNULL button,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);

//
//    const float vertexes[] = {
//        -1.0f, -1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        0.0f,  1.0f, 0.0f,
//    };


}

void amstDrawButton(AmstContext* AMST_NONNULL context, AmstButton* AMST_NONNULL button) {

}
