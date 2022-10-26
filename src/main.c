#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>


void log_error_exit() {
    char msg[] = "The arguments are incorrect.\n"
                 "Usage: demonstrate OPTION FILE\n"
                 "  -g, --grayscale IMG      Save the graysaled image in `grayscaled.png`\n"
                 "  -r, --rotate IMG ANGLE   Save the rotated image with the given angle\n"
                 "                           in `rotated.png`\n"
                 "  -d, --detect IMG         Save the detected grid in `detected_grid.png`\n"
                 "  -c, --cut IMG            Save the images in `img_X.png`\n"
                 "  -s, --solve GRID         Save the result in `GRID.result`\n"
                 "  -n, --neuralNetwork      Show a proof of concept of the neural network\n";

    errx(1, "%s", msg);
}

int main(int argc, char **argv) {
    if (argc < 2)
        log_error_exit();

    if (strcmp(argv[1], "--grayscale") || strcmp(argv[1], "-g")) {
        if (argc != 3)
            log_error_exit();
    }
    else if (strcmp(argv[1], "--rotate") || strcmp(argv[1], "-r")) {
        if (argc != 4)
            log_error_exit();
    }
    else if (strcmp(argv[1], "--detect") || strcmp(argv[1], "-d")) {
        if (argc != 3)
            log_error_exit();
    }
    else if (strcmp(argv[1], "--cut") || strcmp(argv[1], "-c")) {
        if (argc != 3)
            log_error_exit();
    }
    else if (strcmp(argv[1], "--solve") || strcmp(argv[1], "-s")) {
        if (argc != 3)
            log_error_exit();
    }
    else if (strcmp(argv[1], "--neuralNetwork") || strcmp(argv[1], "-n")) {
        if (argc != 2)
            log_error_exit();
    }
    else
        log_error_exit();

    return 0;
}
