#include "matrice.h"

matrice *m1, *m2, *m3, *m4, *m5, *m6, *m7;

void setup(void) {
    m1 = matrice_from_string("1 2,"
                             "3 4");

    m2 = matrice_from_string("5 6,"
                             "7 8");

    m3 = matrice_from_string("1 2 3,"
                             "4 5 6");

    m4 = matrice_from_string("1 2,"
                             "3 4,"
                             "5 6");
}

Test(matrices, test_from_string) {
    setup();

    matrice *m = matrice_new(2, 2);

    matrice_set(m, 0, 0, 1);
    matrice_set(m, 0, 1, 2);
    matrice_set(m, 1, 0, 3);
    matrice_set(m, 1, 1, 4);

    if (!matrice_equals(m, m1)) {
        printf("m1:\n");
        matrice_print(m1);
        printf("m:\n");
        matrice_print(m);
        cr_assert_fail("Parsed matrix is not equal to the expected one");
    }
}

Test(matrices, test_add) {
    setup();

    matrice *expected = matrice_from_string("6 8,"
                                            "10 12");
    matrice *m = matrice_add(m1, m2);

    cr_assert(matrice_equals(m, expected), "Matrices are not equal");
}

Test(matrice, test_sub) {
    setup();

    matrice *expected = matrice_from_string("-4 -4,"
                                            "-4 -4");
    matrice *m = matrice_sub(m1, m2);

    cr_assert(matrice_equals(m, expected), "Matrices are not equal");
}

Test(matrice, test_mul) {
    setup();

    matrice *expected = matrice_from_string("5 12,"
                                            "21 32");

    matrice *m = matrice_mul(m1, m2);

    cr_assert(matrice_equals(m, expected), "Matrices are not equal");
}

Test(matrices, test_dot) {
    setup();

    matrice *expected = matrice_from_string("19 22,"
                                            "43 50");
    matrice *m = matrice_dot(m1, m2);

    cr_assert(matrice_equals(m, expected), "Matrices are not equal");
}

Test(matrices, test_transpose) {
    setup();

    matrice *expected = matrice_from_string("1 3,"
                                            "2 4");
    matrice *m = matrice_transpose(m1);

    cr_assert(matrice_equals(m, expected), "Matrices are not equal");
}

Test(matrices, test_random_generate) {
    setup();

    matrice *m1 = matrice_random(15, 15, -1, 1);
    matrice *m2 = matrice_random(15, 15, -1, 1);

    cr_assert(!matrice_equals(m1, m2),
              "Such big random matrices should not be equal");
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            cr_assert(matrice_get(m1, i, j) >= -1 && matrice_get(m1, i, j) <= 1,
                      "Random matrix is not in range");
            cr_assert(matrice_get(m2, i, j) >= -1 && matrice_get(m2, i, j) <= 1,
                      "Random matrix is not in range");
        }
    }
}

Test(matrices, test_scalar_multiply) {
    setup();

    matrice *expected = matrice_from_string("2 4,"
                                            "6 8");
    matrice_multiply(m1, 2);

    cr_assert(matrice_equals(m1, expected), "Matrices are not equal");
}

double multiply_by_two(double x) { return x * 2; }

Test(matrices, test_map) {
    setup();

    matrice *expected = matrice_from_string("2 4,"
                                            "6 8");
    matrice_map(m1, multiply_by_two);

    cr_assert(matrice_equals(m1, expected), "Matrices are not equal");
}
