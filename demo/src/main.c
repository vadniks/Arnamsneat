/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <stdlib.h>
#include <arnamsneat.h>

int main(void) {
    amstInit();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
        abort();

    SDL_Window* window = SDL_CreateWindow(
        "Title",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        160,
        90,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    amstSetSdlRendererHints();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int msecs = 0;
    SDL_Event event;
    while (msecs < 5000) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) goto end;
            amstProcessEvent(&event);
        }

        msecs += 10;
        SDL_Delay(10);
    }
    end:

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    amstQuit();

    if (SDL_GetNumAllocations() != 0) abort();
    return EXIT_SUCCESS;
}
