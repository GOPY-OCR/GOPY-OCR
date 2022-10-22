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

SDL_Surface *principal_component_analysis(SDL_Surface *image, int connectivity){
    // array of connected components
    int max_components = MAX_COMPONENTS;
    SDL_Surface **components = malloc(sizeof(SDL_Surface *) * MAX_COMPONENTS);
    int *component_sizes = malloc(sizeof(int) * MAX_COMPONENTS);
    int nb_components = 0;

    if(SDL_MUSTLOCK(image)){
        SDL_UnlockSurface(image);
    }

    for(int i = 0; i < image->w; i++){
        for(int j = 0; j < image->h; j++){
            if(!is_pixel_white(image, i, j)){
                // black pixel
                continue;
            }

            int connected = 0;
            for(int k = 0; k < nb_components; k++){
                if(is_connected(components[k], image, i, j, connectivity)){
                    // pixel is connected to a component
                    Uint32 *pixel = getpixel(components[k], i, j);
                    *pixel = SDL_MapRGB(components[k]->format, 255, 255, 255);
                    component_sizes[k]++;
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

                if(nb_components >= max_components){
                    max_components *= 2;
                    components = realloc(components, sizeof(SDL_Surface *) * max_components);
                    component_sizes = realloc(component_sizes, sizeof(int) * max_components);
                }

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

    printf("nb_components = %d, largest component size = %d\n", nb_components, component_sizes[maxi]);

    // free the other components
    for(int i = 0; i < nb_components; i++){
        if(i != maxi){
            SDL_FreeSurface(components[i]);
        }
    }

    return components[maxi];
}

struct pixel{
    int x;
    int y;
};

int is_connected(SDL_Surface *component, SDL_Surface *image, int x, int y, int connectivity){
    queue *q = queue_create();
    struct pixel p = {x, y};
    queue_push(q, &p);

    while(!queue_is_empty(q)){
        struct pixel *p = queue_dequeue(q);

        if(!is_pixel_white(image, p->x, p->y)){
            // black pixel
            continue;
        }

        if(is_pixel_white(component, p->x, p->y)){
            // a path could be found between the pixel and one of the component's pixels
            queue_free(q);
            return 1;
        }

        // add the pixel's neighbors to the queue
        for (int i = -connectivity; i <= connectivity; i++) {
            for (int j = -connectivity; j <= connectivity; j++) {
                if(i == 0 && j == 0){
                    continue;
                }

                struct pixel p2 = {p->x + i, p->y + j};
                queue_push(q, &p2);
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
