#include "utils.h"
#include "hough_transform.h"
#include <SDL2/SDL.h>


int main(int argc, char **argv) {
    SDL_Surface *image = load_image(argv[1]);

    Rect sudoku_square = find_sudoku_grid(image, 18, 1);

    printf("Sudoku square found with corner1: (%d, %d) and corner2: (%d, %d)\n", 
            sudoku_square.p1.x, sudoku_square.p1.y, sudoku_square.p2.x, sudoku_square.p2.y);


    save_image(image, "output.png");

    return 0; 
}
