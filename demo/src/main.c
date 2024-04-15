
#include <stdlib.h>
#include <arnamsneat/arnamsneat.h>
#include <arnamsneat/core.h>
#include <arnamsneat/button.h>
#include <arnamsneat/text.h>
#include <arnamsneat/checkbox.h>
#include <arnamsneat/field.h>

static bool gCChecked = false;

static void buttonAClicked(void) { SDL_Log("button a clicked"); }
static void buttonBClicked(void) { SDL_Log("button b clicked"); }
static void checkboxCClicked(void) { gCChecked = !gCChecked; }

static void fieldInputHandler(const char* AMST_NONNULL input) {

}

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

    AmstContext* context = amstContextCreate(window, renderer, font);

    AmstFieldState* fieldState = amstCreateFieldState();

    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) goto end;
            amstProcessEvent(context, &event);
        }

        amstPrepareToDraw(context);
        int32_t width, height;

        amstButton(context, "A", 10, 10, &buttonAClicked);

        amstGetLastDrawnSizes(context, &width, &height);
        amstButton(context, "Bb", 10 + width + 5, 10, &buttonBClicked);

        amstCheckbox(context, "C", 10, 10 + height + 5, gCChecked, &checkboxCClicked);

        amstGetLastDrawnSizes(context, &width, &height);
        amstText(context, "Text", (SDL_Color) {255, 255, 255, 255}, 10, 10 + height * 2 + 5);

        amstField(context, 100, 100, "Label", fieldState, &fieldInputHandler);

        amstDrawAll(context);
    }
    end:

    amstDestroyFieldState(fieldState);

    amstContextDestroy(context);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    amstQuit();

    if (SDL_GetNumAllocations() != 0) abort();
    return EXIT_SUCCESS;
}
