#include "dataset.h"

dataset *create_dataset(int size) {
    dataset *data = malloc(sizeof(dataset));
    data->inputs = malloc(size * sizeof(matrice *));
    data->targets = malloc(size * sizeof(matrice *));
    data->size = size;
    return data;
}

void free_dataset(dataset *data) {
    for (int i = 0; i < data->size; i++) {
        matrice_free(data->inputs[i]);
        matrice_free(data->targets[i]);
    }
    free(data->inputs);
    free(data->targets);
    free(data);
}

// these values where computed accross the whole dataset previously
// and are used to normalize the inputs
#define IMAGE_MEAN 100.602216505102035171148600056767
#define IMAGE_STD 236.326521859361037058988586068153
matrice *image_to_matrice(SDL_Surface *image) {
    matrice *m = matrice_new(image->w * image->h, 1);

    for (int i = 0; i < image->w; i++) {
        for (int j = 0; j < image->h; j++) {
            Uint8 r, g, b;
            SDL_GetRGB(*getpixel(image, i, j), image->format, &r, &g, &b);
            float value = is_pixel_white(image, i, j) * 255 * 3; // back to binary images for testing
            value = (value - IMAGE_MEAN) / IMAGE_STD; // normalization based on precomputed values
            matrice_set(m, i * image->h + j, 0, value);
        }
    }

    return m;
}

dataset *load_dataset(const char *path, int size) {
    dataset *data = create_dataset(size * 10);
    data->inputs = malloc(size * 10 * sizeof(matrice *));
    data->targets = malloc(size * 10 * sizeof(matrice *));

    int pathle = strlen(path);
    for (int i = 0; i < 10; i++) {
        char *folder = malloc(pathle + 2);
        strcpy(folder, path);
        // last folder character is the digit e.g. "data/training/0"
        folder[pathle] = i + '0';
        folder[pathle + 1] = '\0';

        char **images_paths = list_files(folder, size, 1);

        for (int j = 0; j < size; j++) {
            SDL_Surface *image = load_image(images_paths[j]);

            data->inputs[i * size + j] = image_to_matrice(image);
            data->targets[i * size + j] = matrice_zeros(10, 1);
            matrice_set(data->targets[i * size + j], i, 0, 1);

            SDL_FreeSurface(image);
        }

        for (int j = 0; j < size; j++) {
            free(images_paths[j]);
        }

        free(folder);
        free(images_paths);
    }

    return data;
}


void shuffle_dataset(dataset *data) {
    for (int i = 0; i < data->size; i++) {
        int j = rand() % data->size;
        matrice *tmp = data->inputs[i];
        data->inputs[i] = data->inputs[j];
        data->inputs[j] = tmp;
        tmp = data->targets[i];
        data->targets[i] = data->targets[j];
        data->targets[j] = tmp;
    }
}

dataset *copy_dataset(dataset *data, int deepcopy) {
    dataset *copy = create_dataset(data->size);
    for (int i = 0; i < data->size; i++) {

        if(deepcopy) {
            copy->inputs[i] = matrice_clone(data->inputs[i]);
            copy->targets[i] = matrice_clone(data->targets[i]);
        } else {
            copy->inputs[i] = data->inputs[i];
            copy->targets[i] = data->targets[i];
        }
    }
    return copy;
}

dataset *dataset_slice(dataset *data, int start, int end) {
    // even more shallow copy than copy_dataset with deepcopy = 0
    // this is so that we don't have to worry about freeing
    // the output of this function
    dataset *copy = malloc(sizeof(dataset)); 
    copy->inputs = data->inputs + start;
    copy->targets = data->targets + start;
    copy->size = end - start;
    return copy;
}

