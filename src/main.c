#include "main.h"


void exit(int exit_error) {
    char msg[] = "The arguments are incorrect.\n"
                 "Usage: demonstrate OPTION [FILE]\n"
                 "  -h, --help               Show this help\n"
                 "  -g, --grayscale IMG      Save the graysaled image in `IMG_grayscaled.png`\n"
                 "  -r, --rotate IMG ANGLE   Save the rotated image with the given angle\n"
                 "  -b, --binarization IMG   Save the binarized image in `IMG_bin.png`\n"
                 "                           in `IMG_ANGLE_rotated.png`\n"
                 "  -d, --detect IMG         Save the detected grid in `IMG_detected_grid.png`\n"
                 "  -c, --cut IMG            Save the images in `IMG_X.png`\n"
                 "  -s, --solve GRID         Save the result in `GRID.result`\n"
                 "  -n, --neuralNetwork      Show a proof of concept of the neural network\n";

    errx(exit_error, "%s", msg);
}

/* 
 * Insert the string in `add` before the `.png` of `name`
 */
char *format_final_name(char *name, char *add) {
    char *res = calloc(strlen(name) + strlen(add) + 4, sizeof(char));
    size_t i = 0;
    while (name[i] != '.') {
        res[i] = name[i];
        i++;
    }

    for (size_t j = 0; add[j] == 0; i++, j++)
        res[i] = add[j];

    res[i] = '.';
    res[i + 1] = 'p';
    res[i + 2] = 'n';
    res[i + 3] = 'g';

    printf("%s", res);

    return res;
}

int main(int argc, char **argv) {
    if (argc < 2)
        exit(1);

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        exit(0);
    }
    else if (strcmp(argv[1], "--grayscale") == 0 || strcmp(argv[1], "-g") == 0) {
        printf("Show grayscalisation...\n");

        if (argc != 3)
            exit(1);

    }
    else if (strcmp(argv[1], "--binarization") == 0 || strcmp(argv[1], "-b") == 0) {
        printf("Show binarization...\n");

        if (argc != 3)
            exit(1);

    }
    else if (strcmp(argv[1], "--rotate") == 0 || strcmp(argv[1], "-r") == 0) {
        printf("Show rotation...\n");

        if (argc != 4)
            exit(1);

    }
    else if (strcmp(argv[1], "--detect") == 0 || strcmp(argv[1], "-d") == 0) {
        printf("Show grid detection...\n");

        if (argc != 3)
            exit(1);

        char *final_name = format_final_name(argv[2], "detected_grid");

        SDL_Surface *image = load_image(argv[2]);
        grid_detection(image, 1);
        save_image(image, final_name);
    }
    else if (strcmp(argv[1], "--cut") == 0 || strcmp(argv[1], "-c") == 0) {
        printf("Show cutting image...\n");

        if (argc != 3)
            exit(1);

    }
    else if (strcmp(argv[1], "--solve") == 0 || strcmp(argv[1], "-s") == 0) {
        printf("Show solver...\n");

        if (argc != 3)
            exit(1);

    }
    else if (strcmp(argv[1], "--neuralNetwork") == 0 || strcmp(argv[1], "-n") == 0) {
        printf("Show neural network...\n");

        if (argc != 2)
            exit(1);

    }
    else
        printf("%s", argv[1]);

    return 0;
}
