#include "matrice.h"

#define USE_MULTITHREADING 0
// after doing some quick hand benchmarking,
// it seems that multithreading is not worth it
// under ~100 x 100 matrices
#define MULTITHREADING_THRESHOLD 10000

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
    int max_length = 0;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            int lenght = strlen(double_to_string(matrice_get(m, i, j)));
            if (lenght > max_length)
                max_length = lenght;
        }
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            printf("%*s ", max_length, double_to_string(matrice_get(m, i, j)));
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

double *matrice_get_ref(matrice *m, int row, int column) {
    // the following out of bounds check is commented out
    // because this function is by far the most called
    //if (row >= m->rows || column >= m->columns)
    //    errx(EXIT_FAILURE, "matrice_get_ref: index out of bounds");

    return m->data + (row * m->columns + column);
}

double matrice_get(matrice *m, int row, int column) {
    return *matrice_get_ref(m, row, column);
}

void matrice_set(matrice *m, int row, int column, double value) {
    *matrice_get_ref(m, row, column) = value;
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

int matrice_equals_epsilon(matrice *m1, matrice *m2, double epsilon) {
    if (m1->rows != m2->rows || m1->columns != m2->columns)
        return 0;

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->columns; j++) {
            if (fabs(matrice_get(m1, i, j) - matrice_get(m2, i, j)) > epsilon)
                return 0;
        }
    }

    return 1;
}

void matrice_dot_sthreaded(matrice *m1, matrice *m2, matrice *r){
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->columns; j++) {
            double *sum = matrice_get_ref(r, i, j);
            *sum = 0;
            for (int k = 0; k < m1->columns; k++) {
                *sum += matrice_get(m1, i, k) * matrice_get(m2, k, j);
            }
        }
    }
}

matrice *matrice_dot(matrice *m1, matrice *m2) {
    if (m1->columns != m2->rows)
        errx(EXIT_FAILURE, "matrice_dot: incompatible matrice sizes, "
                            "m1 is %d x %d, m2 is %d x %d",
                            m1->rows, m1->columns, m2->rows, m2->columns);

    matrice *r = matrice_new(m1->rows, m2->columns);

    if (USE_MULTITHREADING && m1->rows * m2->columns > MULTITHREADING_THRESHOLD)
        matrice_dot_mthreaded(m1, m2, r);
    else
        matrice_dot_sthreaded(m1, m2, r);

    return r;
}

// source: www.researchgate.net/publication/220337322_An_Efficient_and_Simple_Algorithm_for_Matrix_Inversion
matrice *matrice_invert(matrice *m){
    if (m->rows != m->columns)
        errx(EXIT_FAILURE, "matrice_invert: matrice is not square (m is %ix%i)",
                m->rows, m->columns);

    double pivot, det = 1.0;
    int i, p, j;
    int size = m->rows;
    matrice *inv = matrice_clone(m);
    for(p = 0; p < size; p++){
        pivot = matrice_get(inv, p, p);
        det *= pivot;

        if(doubleabs(pivot) < 1e-5){
            errx(EXIT_FAILURE, "matrice_invert: matrice is not invertible\n%s",
                    matrice_serialize(m, "m"));
        }

        for(i = 0; i < size; i++){
            *matrice_get_ref(inv, i, p) /= -pivot;
        }

        for(i = 0; i < size; i++){
            if(i != p)
                for(j = 0; j < size; j++)
                    if(j != p){
                        float tmp = matrice_get(inv, p, j) * matrice_get(inv, i, p);
                        *matrice_get_ref(inv, i, j) += tmp;
                    }
        }

        for(j = 0; j < size; j++){
            *matrice_get_ref(inv, p, j) /= pivot;
        }

        *matrice_get_ref(inv, p, p) = 1 / pivot;
    }

    if(doubleabs(det) < 1e-5){
            errx(EXIT_FAILURE, "matrice_invert: matrice is not invertible\n%s",
                    matrice_serialize(m, "m"));
    }

    return inv;
}

matrice *matrice_elementwise_inner(matrice *m1, matrice *m2,
                                   double (*f)(double, double),
                                   const char *function_name) {

    if (m1->rows != m2->rows || m1->columns != m2->columns) {
        errx(EXIT_FAILURE,
             "%s: matrice dimensions do not match, "
             "m1 is %d x %d, m2 is %d x %d",
             function_name, m1->rows, m1->columns, m2->rows, m2->columns);
    }

    matrice *m = matrice_new(m1->rows, m1->columns);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->columns; j++) {
            matrice_set(m, i, j,
                        f(matrice_get(m1, i, j), matrice_get(m2, i, j)));
        }
    }
    return m;
}

matrice *matrice_elementwise(matrice *m1, matrice *m2,
                             double (*f)(double, double)) {
    return matrice_elementwise_inner(m1, m2, f, "matrice_elementwise");
}

double add(double a, double b) { return a + b; }
matrice *matrice_add(matrice *m1, matrice *m2) {
    return matrice_elementwise_inner(m1, m2, &add, "matrice_add");
}

double sub(double a, double b) { return a - b; }
matrice *matrice_sub(matrice *m1, matrice *m2) {
    return matrice_elementwise_inner(m1, m2, &sub, "matrice_sub");
}

double mul(double a, double b) { return a * b; }
matrice *matrice_mul(matrice *m1, matrice *m2) {
    return matrice_elementwise_inner(m1, m2, &mul, "matrice_mul");
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

matrice *matrice_map(matrice *m, double (*f)(double)) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            double *field = matrice_get_ref(m, i, j);
            *field = f(*field);
        }
    }
    return m;
}

void matrice_add_inplace(matrice *dest, matrice *source){
    if (dest->rows != source->rows || dest->columns != source->columns)
        errx(EXIT_FAILURE, "matrice_add_inplace: incompatible matrice sizes, "
                            "dest is %d x %d, source is %d x %d",
                            dest->rows, dest->columns,
                            source->rows, source->columns);

    for (int i = 0; i < dest->rows; i++) {
        for (int j = 0; j < dest->columns; j++) {
            double *dest_field = matrice_get_ref(dest, i, j);
            *dest_field += matrice_get(source, i, j);
        }
    }
}

void matrice_sub_inplace(matrice *dest, matrice *source){
    if (dest->rows != source->rows || dest->columns != source->columns)
        errx(EXIT_FAILURE, "matrice_add_inplace: incompatible matrice sizes, "
                            "dest is %d x %d, source is %d x %d",
                            dest->rows, dest->columns,
                            source->rows, source->columns);

    for (int i = 0; i < dest->rows; i++) {
        for (int j = 0; j < dest->columns; j++) {
            double *dest_field = matrice_get_ref(dest, i, j);
            *dest_field -= matrice_get(source, i, j);
        }
    }
}

matrice *matrice_multiply(matrice *m, double scalar) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            matrice_set(m, i, j, matrice_get(m, i, j) * scalar);
        }
    }

    return m;
}

matrice *matrice_clone(matrice *m) {
    matrice *m_clone = matrice_new(m->rows, m->columns);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            matrice_set(m_clone, i, j, matrice_get(m, i, j));
        }
    }
    return m_clone;
}

double *matrice_max(matrice *m, int *row, int *column) {
    if (row == NULL)
        row = malloc(sizeof(int));

    if (column == NULL)
        column = malloc(sizeof(int));

    double *max = matrice_get_ref(m, 0, 0);
    *row = 0;
    *column = 0;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            double *value = matrice_get_ref(m, i, j);
            if (*value > *max) {
                max = value;
                *row = i;
                *column = j;
            }
        }
    }

    return max;
}

double matrice_sum(matrice *m) {
    double sum = 0;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            sum += matrice_get(m, i, j);
        }
    }
    return sum;
}

double matrice_mean(matrice *m) {
    return matrice_sum(m) / (m->rows * m->columns);
}

// std = standard deviation = écart type = sqrt(variance)
double matrice_std(matrice *m){
    double mean = matrice_mean(m);
    double sum = 0;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            double value = matrice_get(m, i, j);
            sum += (value - mean) * (value - mean);
        }
    }
    return sqrt(sum / (m->rows * m->columns));
}


#define SEPARATOR ';'
#define LINE_SEPARATOR '\n'
char *matrice_serialize(matrice *m, char *name){
    int size = 256;
    if (name != NULL) {
        size += strlen(name);
    }
    int index = 0;
    char *output = malloc(sizeof(char) * size);
    output[index] = '\0';

    if (name != NULL) {
        sprintf(output, "# %s%c", name, LINE_SEPARATOR);
    }
    char *dims = malloc(sizeof(char) * 256);
    sprintf(dims, "%dx%d%c", m->rows, m->columns, LINE_SEPARATOR);
    strcat(output, dims);
    free(dims);

    index = strlen(output);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            if (index + 20 >= size) {
                size *= 2;
                output = realloc(output, sizeof(char) * size);
            }

            char *val = serialize_double(matrice_get(m, i, j));
            size_t le = strlen(val);
            memcpy(output + index, val, le);
            index += le;

            output[index++] = SEPARATOR;
            free(val);
        }
        output[index - 1] = LINE_SEPARATOR;
    }
    output[index] = '\0';

    output = realloc(output, sizeof(char) * (index + 1));

    return output;
}


matrice *matrice_deserialize(char *str, char **endptr){
    // skip name if present
    char *p = str;
    if (*p == '#') {
        while (*p != LINE_SEPARATOR) {
            p++;
        }
        p++;
    }

    // get dimensions
    int rows, columns;
    sscanf(p, "%dx%d", &rows, &columns);
    while (*p != LINE_SEPARATOR) {
        p++;
    }
    p++;

    matrice *m = matrice_new(rows, columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double val = strtod(p, &p);
            matrice_set(m, i, j, val);
            p++;
        }
    }

    if (endptr != NULL) {
        *endptr = p;
    }

    return m;
}


void matrice_to_csv(matrice *m, char *filename, char *name) {
    char *str = matrice_serialize(m, name);
    write_to_file(filename, str);
    free(str);
}

matrice *matrice_read_csv(char *filename) {
    char *str = read_from_file(filename);
    matrice *m = matrice_deserialize(str, NULL);
    free(str);
    return m;
}
