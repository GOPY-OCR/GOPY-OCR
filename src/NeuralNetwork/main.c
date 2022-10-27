#include "main.h"

const char *help = "usage: %s mode [options] [mode options]   \n\
availables modes:                                             \n\
-t, --train: train the neural network                         \n\
-p, --predict: predict the number displayed on the input image\n\
-x, --xor-demo: run the demo for the xor network              \n\
-h, --help: display this help                                 \n\
options:                                                      \n\
-v, -vv, -vvv: set the verbosity level                        \n\
";

int main(int argc, char **argv) {
    if (argc < 2) {
        errx(EXIT_FAILURE, help, argv[0]);
    }

    int verbosity = 0;

    if (argc > 2) {
        if (strcmp(argv[2], "-v") == 0) {
            verbosity = 1;
        } else if (strcmp(argv[2], "-vv") == 0) {
            verbosity = 2;
        } else if (strcmp(argv[2], "-vvv") == 0) {
            verbosity = 3;
        }
    }


    if (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--train") == 0) {
        // TODO: train 
    } else if (strcmp(argv[1], "-p") == 0 ||
               strcmp(argv[1], "--predict") == 0) {
        if (argc < 3) {
            errx(EXIT_FAILURE, "error: file not specified");
        }
        // TODO: predict
        

    } else if (strcmp(argv[1], "-h") == 0 ||
               strcmp(argv[1], "--help") == 0) {


    } else if (strcmp(argv[1], "-x") == 0 || strcmp(argv[1], "--xor-demo") == 0) {
        int verbose_argument = (verbosity > 0) ? 1 : 0;
        int args_offset = 2 + verbose_argument;
        xor_main(verbosity, argc - args_offset, argv + args_offset);
    } else {
        errx(EXIT_FAILURE,
             "unknown mode: %s, use -h or --help to display the help", argv[1]);
    }

    return EXIT_SUCCESS;
}
