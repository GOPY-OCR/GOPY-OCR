#include "main.h"

const char *help = "usage: %s mode [file] \n\
availables modes: \n\
-t, --train: train the neural network \n\
-p, --predict: predict the number displayed on the input image \n\
-h, --help: display this help \
";

int main(int argc, char **argv) {

    if (argc < 2) {
        errx(EXIT_FAILURE, help, argv[0]);
    }

    if (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--train") == 0) {
        train();

    } else if (strcmp(argv[1], "-p") == 0 ||
               strcmp(argv[1], "--predict") == 0) {
        if (argc < 3) {
            errx(EXIT_FAILURE, "error: file not specified");
        }
        predict(argv[2]);

    } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf(help, argv[0]);
        printf("\n");

    } else {
        errx(EXIT_FAILURE,
             "unknown mode: %s, use -h or --help to display the help", argv[1]);
    }

    return EXIT_SUCCESS;
}

int predict(const char *image_path) {
    // !todo
    return -1;
}
