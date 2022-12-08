#include "cli.h"


void exit_help(int error) {
    char msg[] = "Usage: demonstrate OPTION [FILE]\n"
                 "  -h,    --help                    Show this help\n"
                 "  -re,   --resize                  Resize the image to a 500x500 image to speed up the preprocess\n"
                 "  -g,    --grayscale IMG           Save the graysaled image in `IMG_grayscaled.png`\n"
                 "  -cb,   --contrast-brightness IMG Save the image with corrected contrast, brightness\n"
                 "                                   and noise reduced in `IMG_contrast.png`\n"
                 "  -b,    --binarization IMG        Save the binarized image in `IMG_bin.png`\n"
                 "  -r,    --rotate IMG ANGLE        Save the rotated image with the given angle\n"
                 "                                   in `IMG_ANGLE_rotated.png`\n"
                 "  -ar,   --auto-rotate IMG         Save the rotated image\n"
                 "                                   in `IMG_ANGLE_auto_rotated.png`\n"
                 "  -d,    --detect-grid IMG         Save the detected grid in `IMG_detected_grid.png`\n"
                 "  -pc,   --perspective-correct IMG Save the perspective correction of IMG\n"
                 "  -c,    --cut IMG                 Save the images in `IMG_X.png`\n"
                 "  -nn,   --neural-network IMG      Save the predicted grid in `IMG_detected_grid.sudoku`\n"
                 "  -S,    --solve GRID              Save the result in `GRID.result`\n"
                 "  -N,    --neural-network-poc      Show a proof of concept of the neural network\n"
                 "                                   Type `-N` to show help message about neural network\n"
                 "  -P,    --preprocess IMG          Execute the whole preprocess\n"
                 "  -O,    --postprocess GRID \\     Generate an image of the solved grid\n"
                 "              SOLVED OUTPUT\n"
                 "  -A,    --all IMG                 Execute the whole process of the OCR.\n"
                 "                                   Save the detected grid in the same directory of IMG\n"
                 "                                   Returns 0 if everything is good\n"
                 "                                   Returns 1 if the detected grid is unsolvable\n";
                
    
    if (error != 0) {
        printf("The arguments are incorrect.\n");
        printf("%s", msg);
        exit(error);
    }

    printf("%s", msg);
    exit(0);
}

/* 
 * Insert the string in `add` before the `.png` of `name`
 */
char *format_final_name(char *name, char *add) {
    char *res = calloc(strlen(name) + strlen(add) + 5, sizeof(char));
    size_t i = 0;
    while (name[i] != '.') {
        res[i] = name[i];
        i++;
    }

    res[i] = '_';
    i++;

    for (size_t j = 0; add[j] != 0; i++, j++)
        res[i] = add[j];

    res[i] = '.';
    res[i + 1] = 'p';
    res[i + 2] = 'n';
    res[i + 3] = 'g';

    return res;
}

int CLI(int argc, char **argv) {
    if (argc < 2)
        exit_help(1);

    if (SDL_Init(SDL_INIT_VIDEO))
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        exit_help(0);
    }

    else if (strcmp(argv[1], "--resize") == 0 || strcmp(argv[1], "-re") == 0) {
        printf("Show resizing...\n");

        if (argc != 3)
            exit_help(1);

        char *final_name = format_final_name(argv[2], "resized");

        SDL_Surface *image = load_image(argv[2]);
        resize(&image);
        save_image(image, final_name);

        free(final_name);
        SDL_FreeSurface(image);
    }
    
    else if (strcmp(argv[1], "--grayscale") == 0 || strcmp(argv[1], "-g") == 0) {
        printf("Show grayscalisation...\n");

        if (argc != 3)
            exit_help(1);

        char *final_name = format_final_name(argv[2], "grayscaled");

        SDL_Surface *image = load_image(argv[2]);
        resize(&image);
        surface_to_grayscale(image);
        save_image(image, final_name);

        free(final_name);
        SDL_FreeSurface(image);
    }
    
    else if (strcmp(argv[1], "--contrast-brightness") == 0 || strcmp(argv[1], "-cb") == 0) {
        printf("Show contrast and brightness...\n");

        if (argc != 3)
            exit_help(1);

        char *final_name = format_final_name(argv[2], "contrast");

        SDL_Surface *image = load_image(argv[2]);
        resize(&image);
        surface_to_grayscale(image);
        correct_brightness(image);
        save_image(image, final_name);

        free(final_name);
        SDL_FreeSurface(image);
    }
    
    else if (strcmp(argv[1], "--binarization") == 0 || strcmp(argv[1], "-b") == 0) {
        printf("Show binarization...\n");

        if (argc != 3)
            exit_help(1);

        char *final_name = format_final_name(argv[2], "bin");

        SDL_Surface *image = load_image(argv[2]);
        resize(&image);
        surface_to_grayscale(image);
        correct_brightness(image);
        adaptative_binarize(image);
        save_image(image, final_name);

        free(final_name);
        SDL_FreeSurface(image);
    }

    else if (strcmp(argv[1], "--detect-grid") == 0 || strcmp(argv[1], "-d") == 0) {
        printf("Show grid detection...\n");

        if (argc != 3)
            exit_help(1);

        char *final_name = format_final_name(argv[2], "detected_grid");

        SDL_Surface *image = load_image(argv[2]);
        resize(&image);
        surface_to_grayscale(image);
        correct_brightness(image);
        adaptative_binarize(image);
        automatic_rot(&image);
        grid_detection(image, 1, 0);
        save_image(image, final_name);

        free(final_name);
        SDL_FreeSurface(image);
    }
    
    else if (strcmp(argv[1], "--rotate") == 0 || strcmp(argv[1], "-r") == 0) {
        printf("Show rotation...\n");

        if (argc != 4)
            exit_help(1);

        // Transform the angle in a double
        double angle = strtod(argv[3], NULL);

        char *final_name = format_final_name(argv[2], "rotated");

        SDL_Surface *image = load_image(argv[2]);
        manual_rot(&image, angle);
        save_image(image, final_name);

        free(final_name);
        SDL_FreeSurface(image);
    }
    
    else if (strcmp(argv[1], "--auto-rotate") == 0 || strcmp(argv[1], "-ar") == 0) {
        printf("Show automatic rotation...\n");

        if (argc != 3)
            exit_help(1);

        char *final_name = format_final_name(argv[2], "auto_rotated");

        SDL_Surface *image = load_image(argv[2]);
        resize(&image);
        surface_to_grayscale(image);
        correct_brightness(image);
        adaptative_binarize(image);
        automatic_rot(&image);
        save_image(image, final_name);
        SDL_FreeSurface(image);
    }

    else if (strcmp(argv[1], "--perspective-correct") == 0 || strcmp(argv[1], "-pc") == 0) {
        printf("Show perspective correction...\n");

        if (argc != 3)
            exit_help(1);

        char *final_name = format_final_name(argv[2], "perspective");

        SDL_Surface *image = load_image(argv[2]);
        resize(&image);
        surface_to_grayscale(image);
        correct_brightness(image);
        adaptative_binarize(image);
        automatic_rot(&image);
        Quad grid = grid_detection(image, 0, 1);
        perspective_correction(&image, &grid);
        save_image(image, final_name);

        free(final_name);
        SDL_FreeSurface(image);
    }

    else if (strcmp(argv[1], "--cut") == 0 || strcmp(argv[1], "-c") == 0) {
        printf("Show cutting image...\n");

        if (argc != 3)
            exit_help(1);

        SDL_Surface *image = load_image(argv[2]);
        resize(&image);
        surface_to_grayscale(image);
        correct_brightness(image);
        adaptative_binarize(image);
        automatic_rot(&image);
        Quad grid = grid_detection(image, 0, 1);
        perspective_correction(&image, &grid);
        SDL_Surface **splitted = split_sudoku(image);
        neural_network_denoise(splitted);
        neural_network_resize(splitted);

        for (size_t i = 0; i < 81; i++) {
            char str[3] = {0};
            sprintf(str, "%ld", i);
            
            char *final_name = format_final_name(argv[2], str);

            save_image(splitted[i], final_name);

            free(final_name);
            SDL_FreeSurface(splitted[i]);
        }

        SDL_FreeSurface(image);
    }

    else if (strcmp(argv[1], "--neural-network") == 0 || strcmp(argv[1], "-nn") == 0) {
        printf("Show full preprocess and neural network...\n");

        if (argc != 3)
            exit_help(1);

        SDL_Surface **splitted = preprocess(argv[2]);

        int *res = neural_network(splitted);

        printf("Sudoku:\n");
        print_grid(res);

        char *file = calloc(strlen(argv[2]) + 20, sizeof(char));
        strcpy(file, argv[2]);
        char *tmp = strrchr(file, '.');
        *tmp = 0;
        strcat(file, ".sudoku");
        printf("\nSaving to %s...\n", file);
        save_grid_file(file, res);

        free(res);
        free(file);
    }

    else if (strcmp(argv[1], "--solve") == 0 || strcmp(argv[1], "-S") == 0) {
        printf("Show solver...\n");

        if (argc != 3)
            exit_help(1);

        char *file = calloc(strlen(argv[2]) + 7, sizeof(char));
        strcat(file, argv[2]);
        int *board = load_grid_file(file);
        
        Solve(board);
        strcat(file, ".result");
        save_grid_file(file, board);

        free(file);
        free(board);
    }
    
    else if (strcmp(argv[1], "--neural-network-poc") == 0 || strcmp(argv[1], "-N") == 0) {
        printf("Show neural network...\n");

        int verbose = argc > 2 && strcmp(argv[2], "-v") == 0 ? 2 : 1;
        int args_offset = 1 + verbose;

        xor_main(verbose, argc - args_offset, argv + args_offset);
    }

    else if (strcmp(argv[1], "--preprocess") == 0 || strcmp(argv[1], "-P") == 0) {
        printf("Execute the whole preprocess...\n");

        if (argc != 3)
            exit_help(1);

        SDL_Surface **grid = preprocess(argv[2]);
        char *final_name_1 = format_final_name(argv[2], "up_left");
        save_image(grid[0], final_name_1);
        free(final_name_1);
        char *final_name_2 = format_final_name(argv[2], "down_right");
        save_image(grid[80], final_name_2);
        free(final_name_2);
        for (size_t i = 0; i < 81; i++)
            free(grid[i]);

        free(grid);
    }

    else if (strcmp(argv[1], "--postprocess") == 0 || strcmp(argv[1], "-O") == 0) {
        printf("Generate solved image of the sudoku...\n");

        if (argc != 5)
            exit_help(1);

        int *grid = load_grid_file(argv[2]);
        int *solved = load_grid_file(argv[3]);

        SDL_Surface *res = postprocess(grid, solved);

        save_image(res, argv[4]);

        SDL_FreeSurface(res);
        free(grid);
        free(solved);
    }

    else if (strcmp(argv[1], "--all") == 0 || strcmp(argv[1], "-A") == 0) {
        printf("Execute the whole OCR process...\n");

        if (argc != 3)
            exit_help(1);

        SDL_Surface **splitted = preprocess(argv[2]);

        int *grid = neural_network(splitted);
        char *file = calloc(strlen(argv[2]) + 20, sizeof(char));
        strcpy(file, argv[2]);
        char *tmp = strrchr(file, '.');
        *tmp = 0;
        save_grid_file(file, grid);
        
        int *solved = calloc(81, sizeof(int));
        for (size_t i = 0; i < 81; i++)
            solved[i] = grid[i];

        if (!Solve(solved)) {
            printf("Not solvable grid\n");
            return 1;
        }

        else {
            save_grid_file(strcat(file, ".solved"), solved);
            char *tmp2 = strrchr(file, '.');
            *tmp2 = 0;

            SDL_Surface *final_result = postprocess(grid, solved);

            save_image(final_result, strcat(file, "_final_result.png"));
        }

        free(file);
        free(grid);
        free(solved);
    }

    
    else
        exit_help(1);

    return 0;
}
