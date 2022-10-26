#include <stdlib.h>
#include <stdio.h>
#include <err.h>


void log_error_exit() {
    char msg[] = "The arguments are incorrect.\n"
                 "Usage: demonstrate OPTION FILE\n"
                 "  --grayscale IMG      Save the graysaled image in `grayscaled.png`\n"
                 "  --rotate IMG ANGLE   Save the rotated image with the given angle\n"
                 "                       in `rotated.png`\n"
                 "  --detect IMG         Save the detected grid in `detected_grid.png`\n"
                 "  --cut IMG            Save the images in `img_X.png`\n"
                 "  --solve GRID         Save the result in `GRID.result`\n"
                 "  --neuralNetwork      Show a proof of concept of the neural network\n";

    errx(1, "%s", mgs);
}

int main(int argc, char **argv) {
    if (argc < 2)
        log_error_exit();

    switch(argv[1]) {
        case "--grayscale":
            // TODO
            break;

        case "--rotate":
            // TODO
            break;
        
        case "--detect":
            // TODO
            break;

        case "--detect":
            // TODO
            break;

        case "--detect":
            // TODO
            break;

        case "--detect":
            // TODO
            break;

        default:
            log_error_exit();
            break;
    }

    return 0;
}
