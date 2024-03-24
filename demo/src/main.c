
#include <stdlib.h>
#include <arnamsneat.h>

int main(void) {
    amstInit();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
        abort();


    amstQuit();
    return 0;
}
