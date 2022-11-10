#include "grid.h"

int find_grid_number() {
    int count = 0;

    // Init regex part to recognize grid files
    regex_t regex;

    // Open the current dir and list all files in it
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
            if(!regexec(&regex, dir->d_name, 0, NULL, 0))
                count++;

        closedir(d);
    }

    return count;
}



void save_grid_file(const char *filename, const int grid[][9]) {
    FILE *file;
    if ((file = fopen(filename, "w")) == NULL)
        errx(EXIT_FAILURE, "save_grid_file: Can't create and open file %s", filename);
    
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (j == 3 || j == 6)
                fprintf(file, " ");

            if (grid[i][j] == 0)
                fprintf(file, ".");

            else
                fprintf(file, "%i", grid[i][j]);
        }
        if (i == 2 || i == 5)
            fprintf(file, "\n");
        
        fprintf(file, "\n");
    }

    fclose(file);
}



void load_grid_file(const char *filename, int grid[][9]) {
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL)
        errx(EXIT_FAILURE, "Can't open file %s", filename);

    size_t i = 0;
    while (!feof(file) && i < 81) {
        char c = fgetc(file);
        if (c == ' ' || c == '\n')
            continue;

        if (c == '.')
            grid[i / 9][i % 9] = 0;

        else
            grid[i / 9][i % 9] = c - '0';

        i++;
    }
}
