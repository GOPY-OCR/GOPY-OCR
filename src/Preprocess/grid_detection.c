#include "grid_detection.h"

void grid_detection(SDL_Surface *image, int *x1, int *y1, int *x2, int *y2){
    *x1 = 0;
    *y1 = 0;
    *x2 = 0;
    *y2 = 0;

    //int angle = automatic_image_rotation(image);

    //SDL_Surface *rotated_image = image_rotate(max_component, angle);
}

int *project(SDL_Surface *image, int axis){
    int size = axis == 0 ? image->w : image->h;

    int *projection = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++){
        projection[i] = 0;
    }

    for(int i = 0; i < image->w; i++){
        for(int j = 0; j < image->h; j++){
            if(is_pixel_white(image, i, j)){
                projection[axis == 0 ? i : j]++;
            }
        }
    }

    return projection;
}

#define THRESHOLD 127
// image should be locked
int is_pixel_white(SDL_Surface *image, int x, int y){
    Uint32 *pixel = getpixel(image, x, y);

    if(pixel == NULL){
        return 0;
    }

    Uint8 r, g, b;
    SDL_GetRGB(*pixel, image->format, &r, &g, &b);

    return r > THRESHOLD && g > THRESHOLD && b > THRESHOLD;
}

Uint32 *getpixel(SDL_Surface *surface, int x, int y){
    if(x < 0 || x >= surface->w || y < 0 || y >= surface->h){
        return NULL;
    }

    int bpp = surface->format->BytesPerPixel; // = 4
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    return p;
}

float floatabs(float x){return x > 0? x : -x;}

float standard_deviation(int *xs, int size){
    if (size < 2) return 0;

    float mean = 0;

    for (int i = 0; i < size; i++){
        mean += xs[i];
    }

    mean /= size;

    float deviation_sum = 0;

    for (int i = 0; i < size; i++){
        deviation_sum += floatabs(xs[i] - mean);
    }

    return deviation_sum / size;
}
