#include "pixel_utils.h"

Test(grid_detection, test_is_pixel_white){
    setup();

    SDL_LockSurface(binary1);

    int white_pixels[7][2] = {
        {75, 86},
        {166, 89},
        {207, 171},
        {408, 450},
        {480, 518},
        {499, 207},
        {491, 73}
    };

    int black_pixels[7][2] = {
        {113, 50},
        {291, 139},
        {419, 148},
        {332, 481},
        {533, 415},
        {557, 562},
        {0, 0}
    };

    for (int i = 0; i < 7; i++){
        int x = white_pixels[i][0];
        int y = white_pixels[i][1];
        int is_white = is_pixel_white(binary1, x, y);
        cr_assert(is_white, "pixel (%d, %d) is not white", x, y);
    }

    for (int i = 0; i < 7; i++){
        int x = black_pixels[i][0];
        int y = black_pixels[i][1];
        int is_black = !is_pixel_white(binary1, x, y);
        cr_assert(is_black, "pixel (%d, %d) is not black", x, y);
    }
}

int pixel_equals_rgb(SDL_Surface *image, int x, int y, Uint8 r, Uint8 g, Uint8 b){
    Uint32 *pixel = getpixel(image, x, y);
    Uint8 red, green, blue;
    SDL_GetRGB(*pixel, image->format, &red, &green, &blue);
    return red == r && green == g && blue == b;
}

Test(grid_detection, test_get_pixel){
    setup();

    cr_assert(getpixel(binary1, 0, 0) != NULL, "pixel (0, 0) is NULL");
    cr_assert(getpixel(binary1, 557, 562) != NULL, "pixel (557, 562) is NULL");

    // out of bounds pixel should be NULL
    cr_assert(getpixel(binary1, 557, 563) == NULL, "pixel (557, 563) is not NULL");
    cr_assert(getpixel(binary1, 558, 562) == NULL, "pixel (558, 562) is not NULL");
    cr_assert(getpixel(binary1, -1, 0) == NULL, "pixel (-1, 0) is not NULL");
    cr_assert(getpixel(binary1, 0, -1) == NULL, "pixel (0, -1) is not NULL");


    cr_assert(pixel_equals_rgb(binary2, 416, 77, 255, 255, 255), "pixel (416, 77) is not (255, 255, 255)");
    cr_assert(pixel_equals_rgb(binary2, 392, 176, 255, 255, 255), "pixel (392, 176) is not (255, 255, 255)");
    cr_assert(pixel_equals_rgb(binary2, 376, 44, 255, 255, 255), "pixel (376, 44) is not (255, 255, 255)");
    cr_assert(pixel_equals_rgb(binary2, 364, 121, 255, 255, 255), "pixel (364, 121) is not (255, 255, 255)");
}
