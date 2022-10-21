#include "grid_detection.h"

void grid_detection(SDL_Surface *image, int *x1, int *y1, int *x2, int *y2){
    *x1 = 0;
    *y1 = 0;
    *x2 = 0;
    *y2 = 0;

    SDL_Surface *max_component = principal_component_analysis(image, 3);

    //int angle = automatic_image_rotation(max_component);

    //SDL_Surface *rotated_image = image_rotate(max_component, angle);
}

// Returns an image containing only
// the largest shape of connected pixels
// in the input image
#define MAX_COMPONENTS 100
SDL_Surface *principal_component_analysis(SDL_Surface *image, int connectivity){
    // array of connected components
    SDL_Surface **components = malloc(sizeof(SDL_Surface *) * MAX_COMPONENTS);
    int *component_sizes = malloc(sizeof(int) * MAX_COMPONENTS);
    int nb_components = 0;

    for(int i = 0; i < image->w; i++){
        for(int j = 0; j < image->h; j++){
            if(!is_pixel_white(image, i, j)){
                // black pixel
                continue;
            }

            int connected = 0;
            for(int k = 0; k < nb_components; k++){
                if(is_connected(components[k], i, j, connectivity)){
                    // pixel is connected to a component
                    Uint32 *pixel = getpixel(components[k], i, j);
                    *pixel = SDL_MapRGB(components[k]->format, 255, 255, 255);

                    connected = 1;
                    break;
                }
            }

            if(!connected){
                // pixel is not connected to any component
                // => create a new component
                SDL_Surface *component = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0, 0, 0, 0);
                Uint32 *pixel = getpixel(component, i, j);
                *pixel = SDL_MapRGB(component->format, 255, 255, 255);

                components[nb_components] = component;
                component_sizes[nb_components] = 1;
                nb_components++;
            }
        }
    }

    // find the largest component
    int maxi = 0;
    for(int i = 1; i < nb_components; i++){
        if(component_sizes[i] > component_sizes[maxi]){
            maxi = i;
        }
    }

    // free the other components
    for(int i = 0; i < nb_components; i++){
        if(i != maxi){
            SDL_FreeSurface(components[i]);
        }
    }

    return components[maxi];
}

// Returns true if the pixel at (x, y) is connected
// to a component via a path in the image
// 
// connectivity: number of pixels to check around the pixel
int is_connected(SDL_Surface *component, int x, int y, int connectivity){
    for(int i = x - connectivity; i <= x + connectivity; i++){
        for(int j = y - connectivity; j <= y + connectivity; j++){
            if(i < 0 || i >= component->w || j < 0 || j >= component->h){
                continue;
            }
            Uint32 *pixel = getpixel(component, i, j);
            if(is_pixel_white(component, i, j)){
                // a neighbor pixel is white
                return 1;
            }
        }
    }
    return 0;
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

int is_pixel_white(SDL_Surface *image, int x, int y){
    Uint32 *pixel = getpixel(image, x, y);

    Uint8 r, g, b;
    SDL_GetRGB(pixel, image->format, &r, &g, &b);
    return r == 0 && g == 0 && b == 0;
}

// magic function from the internet
Uint32 *getpixel(SDL_Surface *surface, int x, int y){
    int bpp = surface->format->BytesPerPixel; // = 4
    Uint32 *p = (Uint32 *)surface->pixels + y * surface->pitch + x * bpp;
    return p;
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
