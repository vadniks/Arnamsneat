
#include <arnamsneat/button.h>
#include <arnamsneat/text.h>
#include "internal.h"
#include "context.h"
#include "defs.h"

void amstGetButtonMetrics(
    int32_t textWidth,
    int32_t textHeight,
    int32_t* AMST_NONNULL width,
    int32_t* AMST_NONNULL height
) {
    *width = textWidth + 10;
    *height = textHeight + 10;
}

void amstDrawButton(AmstContext* AMST_NONNULL context, AmstButton* AMST_NONNULL button) {
    defsAssert(gInitialized);
    defsAssert(button->x >= 5 && button->y >= 5);

    int32_t textWidth, textHeight;
    amstGetTextMetrics(context, button->text, &textWidth, &textHeight);

    const bool mouseHovered =
        context->mouseX >= button->x - 5 && context->mouseX <= button->x + textWidth + 10 &&
        context->mouseY >= button->y - 5 && context->mouseY <= button->y + textHeight + 10;

    const bool mouseClicked = mouseHovered && context->mouseDown;

    SDL_Color color =
        mouseClicked
        ? ((SDL_Color) {50, 50, 50, 50})
        : mouseHovered
          ? ((SDL_Color) {127, 127, 127, 127})
          : ((SDL_Color) {255, 255, 255, 255});

    SDL_Texture* texture = renderText(context, button->text, color, nullptr, nullptr);

    SDL_RenderCopy(
        context->renderer,
        texture,
        nullptr,
        &((SDL_Rect) {button->x, button->y, textWidth, textHeight})
    );
    SDL_DestroyTexture(texture);

    uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(context->renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(context->renderer, &((SDL_Rect) {button->x - 5, button->y - 5, textWidth + 10, textHeight + 10}));
    SDL_SetRenderDrawColor(context->renderer, r, g, b, a);

    if (mouseClicked) {
        context->mouseDown = false;
        button->clickHandler();
    }
}
