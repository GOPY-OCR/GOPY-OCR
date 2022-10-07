#include "matrice.h"

matrice *matrice_new(int rows, int columns) {
    matrice *m = malloc(sizeof(matrice));
    m->rows = rows;
    m->columns = columns;
    m->data = malloc(sizeof(double) * rows * columns);

    if (m->data == NULL)
        errx(EXIT_FAILURE,
             "Error allocating memory for matrice of size %d x %d\n", rows,
             columns);

    return m;
}

void matrice_free(matrice *m) {
    free(m->data);
    free(m);
}

void matrice_print(matrice *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            printf("%f ", matrice_get(m, i, j));
        }
        printf("\n");
    }
}

int count_chars(char *str, char c) {
    int count = 0;
    for (; *str != '\0'; str++)
        if (*str == c)
            count++;

    return count;
}

#define MAX_PARSING_COLUMNS 1000
matrice *matrice_from_string(char *str) {
    char *line, *strcopy;
    matrice *m;

    strcopy = strdup(str);

    if ((line = strsep(&strcopy, ","))) {
        int columns = 0;
        double first_line[MAX_PARSING_COLUMNS];
        char *number;

        while ((number = strsep(&line, " "))) {
            if (columns >= MAX_PARSING_COLUMNS) {
                errx(EXIT_FAILURE,
                     "matrice_from_string: more than %i columns to parse, "
                     "aborting",
                     MAX_PARSING_COLUMNS);
            }
            first_line[columns] = atof(number);
            columns++;
        }

        int rows = count_chars(str, ',') + 1;
        m = matrice_new(rows, columns);

        for (int i = 0; i < columns; i++) {
            matrice_set(m, 0, i, first_line[i]);
        }

        // free(first_line);

        int row = 1;
        int column;
        while ((line = strsep(&strcopy, ","))) {
            column = 0;
            while ((number = strsep(&line, " "))) {
                if (column >= columns) {
                    errx(EXIT_FAILURE,
                         "matrice_from_string: row %i has more columns than "
                         "row 0, "
                         "aborting",
                         row);
                }
                matrice_set(m, row, column, atof(number));
                column++;
            }
            if (column != columns) {
                errx(EXIT_FAILURE,
                     "matrice_from_string: row %i has less columns than row 0, "
                     "aborting",
                     row);
            }
            row++;
        }
        if (row != rows) {
            errx(EXIT_FAILURE,
                 "matrice_from_string: matrice has leading commas, aborting");
        }

        free(strcopy);

        return m;
    } else {
        return matrice_new(0, 0);
    }
}

double matrice_get(matrice *m, int row, int column) {
    return *(m->data + (row * (m->columns) + column));
}

void matrice_set(matrice *m, int row, int column, double value) {
    double *field = m->data + (row * (m->columns) + column);
    *field = value;
}

double random_double(double min, double max) {
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

matrice *matrice_random(int rows, int columns, double min, double max) {
    matrice *m = matrice_new(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrice_set(m, i, j, random_double(min, max));
        }
    }
    return m;
}

matrice *matrice_zeros(int rows, int columns) {
    matrice *m = matrice_new(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrice_set(m, i, j, 0);
        }
    }
    return m;
}

int matrice_equals(matrice *m1, matrice *m2) {
    if (m1->rows != m2->rows || m1->columns != m2->columns)
        return 0;

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->columns; j++) {
            if (matrice_get(m1, i, j) != matrice_get(m2, i, j))
                return 0;
        }
    }

    return 1;
}

matrice *matrice_dot(matrice *m1, matrice *m2) {
    matrice *m = matrice_new(m1->rows, m2->columns);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->columns; j++) {
            double sum = 0;
            for (int k = 0; k < m1->columns; k++) {
                sum += matrice_get(m1, i, k) * matrice_get(m2, k, j);
            }
            matrice_set(m, i, j, sum);
        }
    }
    return m;
}

matrice *matrice_add(matrice *m1, matrice *m2) {
    if (m1->rows != m2->rows || m1->columns != m2->columns) {
        errx(EXIT_FAILURE,
             "matrice_add: matrice dimensions do not match, m1 is %d x %d, m2 "
             "is "
             "%d x %d",
             m1->rows, m1->columns, m2->rows, m2->columns);
    }
    matrice *m = matrice_new(m1->rows, m1->columns);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->columns; j++) {
            matrice_set(m, i, j, matrice_get(m1, i, j) + matrice_get(m2, i, j));
        }
    }
    return m;
}

matrice *matrice_transpose(matrice *m) {
    matrice *m_t = matrice_new(m->columns, m->rows);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            matrice_set(m_t, j, i, matrice_get(m, i, j));
        }
    }
    return m_t;
}

void matrice_map(matrice *m, double (*f)(double)){
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            matrice_set(m, i, j, f(matrice_get(m, i, j)));
        }
    }
}
