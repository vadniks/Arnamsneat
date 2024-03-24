
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

    SDL_Delay(1000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    amstQuit();

    if (SDL_GetNumAllocations() != 0) abort();
    return EXIT_SUCCESS;
}
