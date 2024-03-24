
#include <stdlib.h>
#include <arnamsneat.h>

int main(void) {
    arnamsneatInit();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
        abort();



    arnamsneatQuit();
    return 0;
}
