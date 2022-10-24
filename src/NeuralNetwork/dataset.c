#include "dataset.h"


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

        char **images_paths = list_files(folder, size);

        for (int j = 0; j < size; j++) {
            SDL_Surface *image = load_image(images_paths[j]);

            // !TODO: convert image to input vector
            // !TODO: set target vector
            SDL_FreeSurface(image);
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


dataset *create_dataset(int size) {
    dataset *data = malloc(sizeof(dataset));
    data->inputs = malloc(size * sizeof(matrice *));
    data->targets = malloc(size * sizeof(matrice *));
    data->size = size;
    return data;
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


char **list_files(const char *path, int n) {
    DIR *dir;
    struct dirent *ent;
    char **files = malloc(n * sizeof(char *));
    int i = 0;

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL && i < n) {
            if (ent->d_type == DT_REG) {
                files[i] = malloc(strlen(ent->d_name) + 1);
                strcpy(files[i], ent->d_name);
                i++;
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }

    free(files);
    free(dir);

    return files;
}
