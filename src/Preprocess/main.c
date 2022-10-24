#include "utils.h"
#include "hough_transform.h"
#include "flood_fill.h"
#include <SDL2/SDL.h>


int main(int argc, char **argv) {
    SDL_Surface *image = load_image(argv[1]);

    Uint32 white = SDL_MapRGB(image->format, 255, 255, 255);
    Uint32 black = SDL_MapRGB(image->format, 0, 0, 0);

    flood_fill(image, (Point) {image->w / 2, image->h / 2}, white);

    Rect sudoku_square = find_sudoku_grid(image, strtol(argv[2], NULL, 10), 1);

    printf("Sudoku square found with corner1: (%d, %d) and corner2: (%d, %d)\n", 
            sudoku_square.p1.x, sudoku_square.p1.y, sudoku_square.p2.x, sudoku_square.p2.y);


    save_image(image, "output.png");

    return 0; 
}
