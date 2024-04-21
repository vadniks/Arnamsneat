/*
  Arnamsneat (demo) - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <stdlib.h>
#include <arnamsneat/arnamsneat.h>
#include <arnamsneat/core.h>
#include <arnamsneat/button.h>
#include <arnamsneat/text.h>
#include <arnamsneat/checkbox.h>
#include <arnamsneat/field.h>
#include <arnamsneat/infiiteProgressbar.h>
#include <arnamsneat/radioButon.h>

const int TEXTS_PER_LIST_PAGE = 8, TEXTS_COUNT = TEXTS_PER_LIST_PAGE * 3;

static bool gCChecked = false;
static bool gDChecked = false;
static int gListOffset = 0;
static char gListButton = 0;

static void up(void) {
    if (gListOffset > 0)
        gListOffset -= 1;
}

static void down(void) {
    if (gListOffset + 1 < TEXTS_COUNT)
        gListOffset += 1;
}

static void checkboxCClicked(void) { gCChecked = !gCChecked; }
static void radioButtonClicked(void) { gDChecked = !gDChecked; }
static void listButtonClicked(void) { SDL_Log("list button %c clicked", gListButton); }

int main(void) {
    amstInit();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
        abort();
    if (TTF_Init() != 0)
        abort();

    const int scale = 5;

    SDL_Window* window = SDL_CreateWindow(
        "Title",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        160 * scale,
        90 * scale,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    SDL_SetWindowMinimumSize(window, 160 * scale, 90 * scale);

    amstSetSdlRendererHints();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TTF_Font* font = TTF_OpenFont("res/RobotoMono.ttf", 24);

    AmstContext* context = amstCreateContext(window, renderer, font);

    AmstFieldState* fieldState1 = amstCreateFieldState();
    AmstFieldState* fieldState2 = amstCreateFieldState();

    const int textSize = 10;
    char** texts = SDL_malloc(TEXTS_COUNT * sizeof(void*));

    for (int i = 0; i < TEXTS_COUNT; i++) {
        texts[i] = SDL_malloc(textSize * sizeof(char));

        SDL_memset(texts[i], 'a' + i, textSize - 1);
        texts[i][textSize - 1] = 0;
    }

    int textWidth, textHeight;
    amstGetTextMetrics(context, "AAAAAAAAAA", &textWidth, &textHeight);

    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) goto end;
            amstProcessEvent(context, &event);

            if (event.type == SDL_MOUSEWHEEL) {
                if (event.wheel.y > 0)
                    up();
                else
                    down();
            }
        }

        amstPrepareToDraw(context);
        int32_t width, height;

        amstButton(context, "Up", 10, 10, &up);

        amstGetLastDrawnSizes(context, &width, &height);
        amstButton(context, "Down", 10 + width + 5, 10, &down);

        amstCheckbox(context, "C", 10, 10 + height + 5, gCChecked, &checkboxCClicked);

        amstGetLastDrawnSizes(context, &width, &height);
        amstText(context, "Text", AMST_FOREGROUND_COLOR, 10, 10 + height * 2 + 5);

        amstField(context, 100, 100, "Label 1", fieldState1);

//        amstGetLastDrawnSizes(context, &width, &height);
//        amstField(context, 100 + width + 5, 100, "Label 2", fieldState2);

        amstInfiniteProgressbar(context, 100, 200);

        amstRadioButton(context, "ddd", 100, 400, gDChecked, &radioButtonClicked);

        for (int i = 0; i < TEXTS_PER_LIST_PAGE; i++) {// aka list widget
            if (i + gListOffset >= TEXTS_COUNT) break;
            amstText(context, texts[i + gListOffset], AMST_FOREGROUND_COLOR, 500, i * 50);
            gListButton = (char) ('a' + i + gListOffset);
            amstButton(context, (char[1]) {gListButton}, 650, i * 50, &listButtonClicked);
        }

        amstDrawAll(context);
    }
    end:

    for (int i = 0; i < TEXTS_COUNT; i++)
        SDL_free(texts[i]);
    SDL_free(texts);

    char* field1Text = amstFieldText(fieldState1);
    char* field2Text = amstFieldText(fieldState2);
    SDL_Log("label 1: %s; label 2: %s", field1Text, field2Text);
    SDL_free(field1Text);
    SDL_free(field2Text);

    amstDestroyFieldState(fieldState1);
    amstDestroyFieldState(fieldState2);

    amstDestroyContext(context);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    amstQuit();

    if (SDL_GetNumAllocations() != 0) abort();
    return EXIT_SUCCESS;
}
