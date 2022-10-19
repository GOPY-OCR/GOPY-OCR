#include "grid_detection.h"

void grid_detection(SDL_Surface *image, int *x1, int *y1, int *x2, int *y2){
    *x1 = 0;
    *y1 = 0;
    *x2 = 0;
    *y2 = 0;

    SDL_Surface *max_component = max_component_detection(image);

    int angle = automatic_image_rotation(max_component);

    SDL_Surface *rotated_image = image_rotate(max_component, angle);
}

SDL_Surface *max_convex_component(SDL_Surface *image);

int *project(SDL_Surface *image, int axis){
    int size = axis == 0 ? image->w : image->h;

    int *projection = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++){
        projection[i] = 0;
    }

    for(int i = 0; i < image->w; i++){
        for(int j = 0; j < image->h; j++){
            Uint32 pixel = getpixel(image, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if(r == 0 && g == 0 && b == 0){
                projection[axis == 0 ? i : j]++;
            }
        }
    }

    return projection;
}


// magic function from the internet
Uint32 getpixel(SDL_Surface *surface, int x, int y){
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp){
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
    }
}

float floatabs(float x){return x > 0? x : -x;}

// aka écart type
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


