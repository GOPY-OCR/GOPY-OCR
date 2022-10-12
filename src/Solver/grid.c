#include "grid.h"

int find_grid_number() {
    int count = 0;

    // Init regex part to recognize grid files
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "grid_[0-9][0-9]", REG_EXTENDED);

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

void save_grid_file(const int grid[81], const char *filename) {
    FILE *file;
    if ((file = fopen(filename, 'w')) == NULL)
        errx(EXIT_FAILURE, "Can't create and open file %s", filename);
    
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (j == 3 || j == 6)
                fprintf(file, " ");

            if (grid[i * 9 + j] == 0)
                fprintf(file, ".");

            else
                fprintf(file, "%i", grid[i * 9 + j]);
        }
        if (i == 3 || i == 6)
            fprintf(file, "\n");
        
        fprintf(file, "\n");
    }

    fclose(file);
}
