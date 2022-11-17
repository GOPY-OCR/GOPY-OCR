#include "create_image.h"

int is_initial_number(int x, int y, int *grid) {
    return grid[x * 9 + y] == 0;
}

void draw_grid(SDL_Surface *res) {
    SDL_FillRect(res, NULL, GRID_COLOR);
    
    SDL_Rect *fills = calloc(BOARDSIZE * BOARDSIZE, sizeof(SDL_Rect));

    for(size_t i = 0; i < BOARDSIZE * BOARDSIZE; i++) {
        fills->x = (i % BOARDSIZE) * CELL_SIZE;
        fills->y = (i / BOARDSIZE) * CELL_SIZE;
        fills->w = CELL_SIZE;
        fills->h = CELL_SIZE;
    }

    SDL_FillRects(res, fills, BOARDSIZE * BOARDSIZE, BACK_COLOR);

    free(fills);
}

void add_number(SDL_Surface *res, int x, int y, int number, int *grid) {
    TTF_Font *font = TTF_OpenFont(FONT, 24);
    SDL_Color color = is_initial_number(x, y, grid) ? OLD_NUMBER_COLOR : NEW_NUMBER_COLOR;

    char msg[] = number == 0 ? " " : { number + 48, 0 };
    SDL_Surface* letter = TTF_RenderText_Solid(font, msg, color);

    SDL_Rect msg_rect;
    msg_rect.x = x * CELL_SIZE;
    msg_rect.y = y * CELL_SIZE;
    msg_rect.w = CELL_SIZE;
    msg_rect.h = CELL_SIZE;

    SDL_BlitSurface(letter, NULL, res, &msg_rect);

    SDL_FreeSurface(letter);
}
