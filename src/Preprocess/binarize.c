#include "binarize.h"

void binarize(SDL_Surface *base, int threshold, SDL_Surface *result)
{
    Uint32 *bpixels = base->pixels;
    Uint32 *rpixels = result->pixels;
    size_t len = base->w * base->h;
    for (size_t i = 0; i < len; i++)
        rpixels[i] = ((Uint8) bpixels[i]) >= threshold ? 0 : 0xFFFFFF;
}

void otsu_binarize(SDL_Surface *base){
    SDL_LockSurface(base);
    int threshold = find_threshold(base);
    binarize(base, threshold, base);
    SDL_UnlockSurface(base);
}

int find_threshold(SDL_Surface *base)
{
    int max = 0;
    for (int i = 0; i < base->w; i++)
        for (int j = 0; j < base->h; j++)
        {
            int v = getpixelgray(base, i, j);
            if (v > max)
                max = v;
        }    

    int best_threshold = 0;
    double min_otsu = INFINITY;

    for (int threshold = 0; threshold < max; threshold++)
    {
        double otsu = compute_otsu_criteria(base, threshold);
        if (otsu < min_otsu)
        {
            min_otsu = otsu;
            best_threshold = threshold;
        }
    }

    return best_threshold;
}

double compute_otsu_criteria(SDL_Surface *base, int threshold)
{
    SDL_Surface *thresholded = SDL_CreateRGBSurface(0, base->w, base->h, 32, 0, 0, 0, 0);

    SDL_LockSurface(thresholded);
    binarize(base, threshold, thresholded);
    SDL_UnlockSurface(thresholded);

    matrice *m = matrice_from_surface(thresholded);
    double nb_pixels = base->w * base->h;
    double count = matrice_sum(m) / 255.0;
    double weight1 = count / nb_pixels;
    double weight0 = 1.0 - weight1;

    if (weight0 == 0.0 || weight1 == 0.0)
        return INFINITY;

    Vector *val_pixels1 = vector_new(nb_pixels);
    Vector *val_pixels0 = vector_new(nb_pixels);

    for (int i = 0; i < base->w; i++)
        for (int j = 0; j < base->h; j++)
        {
            double bin = matrice_get(m, i, j);
            int *val = malloc(sizeof(int));
            *val = getpixelgray(base, i, j);

            if (bin < 128)
                vector_push(val_pixels0, (void *) val);
            else
                vector_push(val_pixels1, (void *) val);
        }

    double var0 = pixel_variance(val_pixels0);
    double var1 = pixel_variance(val_pixels1);

    double criteria = weight0 * var0 + weight1 * var1;

    vector_free(val_pixels0);
    vector_free(val_pixels1);
    matrice_free(m);
    SDL_FreeSurface(thresholded);

    return criteria;
}

double pixel_variance(Vector *v)
{
    double sum = 0.0;
    for (size_t i = 0; i < v->size; i++)
        sum += *(int *) vector_get(v, i);

    double mean = sum / v->size;

    sum = 0.0;
    for (size_t i = 0; i < v->size; i++){
        double val = *(int *) vector_get(v, i);
        sum += (val - mean) * (val - mean);
    }

    return sum / v->size;
}
