
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
        160 * 5,
        90 * 5,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    amstSetSdlRendererHints();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    TTF_Font* font = TTF_OpenFont("res/RobotoMono.ttf", 1);
    AmstContext* context = amstContextCreate(window, renderer, font);

    int msecs = 0;
    SDL_Event event;
    while (msecs < 5000) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) goto end;
            amstProcessEvent(&event);
        }

        amstDraw(context);
        msecs += 10;
        SDL_Delay(10);
    }
    end:

    amstContextDestroy(context);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    amstQuit();

    if (SDL_GetNumAllocations() != 0) abort();
    return EXIT_SUCCESS;
}
