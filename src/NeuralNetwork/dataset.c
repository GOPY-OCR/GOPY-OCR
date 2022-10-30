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


matrice *image_to_matrice(SDL_Surface *image) {
    matrice *m = matrice_new(image->w * image->h, 1);
    for (int i = 0; i < image->w; i++) {
        for (int j = 0; j < image->h; j++) {
            Uint32 pixel = *getpixel(image, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            double value = (r + g + b) / 3.0 / 255.0;
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


char **list_files(const char *path, int n, int append_path) {
    DIR *dir;
    struct dirent *ent;
    char **files = malloc(n * sizeof(char *));
    int i = 0;

    int pathle = strlen(path);
    pathle -= pathle > 0 && path[pathle - 1] == '/'; // ignore trailing slash
    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL && i < n) {
            if (ent->d_type == DT_REG) {
                if (append_path) {
                    int filele = strlen(ent->d_name);
                    files[i] = malloc(pathle + filele + 2);
                    strcpy(files[i], path);
                    files[i][pathle] = '/';
                    strcpy(files[i] + pathle + 1, ent->d_name);
                } else {
                    files[i] = malloc(strlen(ent->d_name) + 1);
                    strcpy(files[i], ent->d_name);
                }
                if (files[i] != NULL) {
                    i++;
                }
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }

    return files;
}
