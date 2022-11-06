#include "str_utils.h"

#define DOUBLE_PRECISION 13

char *float_to_string(float d) {
    char *str = malloc(100);
    sprintf(str, "%.*f", DOUBLE_PRECISION, d);

    // remove trailing zeros
    char *p = str + strlen(str) - 1;
    while (*p == '0') {
        *p = '\0';
        p--;
    }

    // remove trailing dot
    if (*p == '.') {
        *p = '\0';
        p--;
    }

    str = realloc(str, strlen(str) + 1);

    return str;
}


void write_to_file(char *filename, char *data) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        errx(1, "write_to_file: Could not open file %s\n", filename);
    }

    fprintf(f, "%s", data);
    fclose(f);
}

char *read_from_file(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        errx(1, "read_from_file: Could not open file %s\n", filename);
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *data = malloc(fsize + 1);
    if(fread(data, fsize, 1, f) != 1) {
        errx(1, "read_from_file: Could not read file %s\n", filename);
    }
    fclose(f);

    data[fsize] = '\0';

    return data;
}
