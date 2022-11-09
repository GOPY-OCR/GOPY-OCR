#include "str_utils.h"

#define DOUBLE_PRECISION 13

void remove_trailing_zeros(char *str) {
    char *p = str;
    while (*p == '0') {
        *p = '\0';
        p--;
    }

    // remove trailing dot
    if (*p == '.') {
        *p = '\0';
        p--;
    }
}

#define MAX_FLOAT_STR_LEN 100
char *float_to_string(float f) {
    char *str = malloc(MAX_FLOAT_STR_LEN);

    sprintf(str, "%.*f", DOUBLE_PRECISION, f);

    remove_trailing_zeros(str + strlen(str) - 1);

    return str;
}

char *serialize_float(float f){
    char *str = malloc(MAX_FLOAT_STR_LEN);
    
    sprintf(str, "%.*g", DOUBLE_PRECISION, f);

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
