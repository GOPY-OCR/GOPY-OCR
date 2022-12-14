#include "create_image.h"

void add_number(SDL_Surface *res, int x, int y, int number, int *grid) {
    // If there is no number, return and to nothing
    if (number == 0)
        return;

    SDL_Color color = grid[x + y * BOARDSIZE] == 0 ? NEW_NUMBER_COLOR : OLD_NUMBER_COLOR;

    if (TTF_Init() < 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    TTF_Font *font = TTF_OpenFont(FONT, CELL_SIZE / 4 * 3);
    if (font == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    char msg[2] = {0};
    msg[0] = number == 0 ? 0 : number + 48;
    SDL_Surface* letter = TTF_RenderText_Solid(font, msg, color);

    TTF_CloseFont(font);

    SDL_Rect msg_rect;
    msg_rect.x = x * CELL_SIZE + (CELL_SIZE - letter->w) / 2;
    msg_rect.y = y * CELL_SIZE;
    msg_rect.w = CELL_SIZE;
    msg_rect.h = CELL_SIZE;

    SDL_BlitSurface(letter, NULL, res, &msg_rect);

    SDL_FreeSurface(letter);
}
