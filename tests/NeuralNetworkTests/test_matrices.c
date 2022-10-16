#include "matrice.h"

matrice *m1, *m2, *m3, *m4, *big1, *big2;
char *serialized_big1;

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
    big1 = matrice_from_string("9.123 12.73 8129 837 2871 1 2 3 4,"
                               "1 2 3 4 5 6 7 8 9,"
                               "9 8 7 6 5 4 3 2 1,"
                               "0 0 0 0 0 0 0 0 0,"
                               "999 999 999 999 999 999 999 999 999,"
                               "-9999 -9999 -9999 -9999 -9999 -9999 -9999 -9999 -9999");

    serialized_big1 = "# big1\n"
                            "6x9\n"
                            "9.123;12.73;8129;837;2871;1;2;3;4\n"
                            "1;2;3;4;5;6;7;8;9\n"
                            "9;8;7;6;5;4;3;2;1\n"
                            "0;0;0;0;0;0;0;0;0\n"
                            "999;999;999;999;999;999;999;999;999\n"
                            "-9999;-9999;-9999;-9999;-9999;-9999;-9999;-9999;-9999\n";

    big2 = matrice_from_string("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41");
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
    cr_assert_eq(matrice_get(big1, 0, 0), 9.123);
    cr_assert_eq(matrice_get(big1, 5, 0), -9999);
    cr_assert_eq(matrice_get(big1, 5, 8), -9999);
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

Test(matrices, test_clone) {
    setup();

    matrice *m = matrice_clone(m1);

    cr_assert(matrice_equals(m, m1), "Matrices are not equal");
}

Test(matrices, test_max) {
    setup();

    int i;
    int j;

    matrice_max(m1, &i, &j);


    cr_assert(i == 1 && j == 1, "Max is not in the right place");

}

Test(matrices, test_sum) {
    setup();

    double sum = matrice_sum(m1);

    cr_assert(sum == 10, "Sum is not equal to 10");
}

Test(matrices, test_serialize) {
    setup();

    cr_assert_str_eq(matrice_serialize(m1, "m1"), "# m1\n"
                                                  "2x2\n"
                                                  "1;2\n"
                                                  "3;4\n");

    cr_assert_str_eq(matrice_serialize(m1, NULL), "2x2\n"
                                                  "1;2\n"
                                                  "3;4\n");

    cr_assert_str_eq(matrice_serialize(big1, "big1"), serialized_big1);

}

Test(matrices, test_deserialize) {
    setup();

    matrice *m = matrice_deserialize(serialized_big1);

    cr_assert(matrice_equals(m, big1), "Matrices are not equal");

    cr_assert(matrice_equals(m1, matrice_deserialize(matrice_serialize(m1, NULL))), "Matrices are not equal");
    cr_assert(matrice_equals(m2, matrice_deserialize(matrice_serialize(m2, NULL))), "Matrices are not equal");
    cr_assert(matrice_equals(m3, matrice_deserialize(matrice_serialize(m3, NULL))), "Matrices are not equal");
    cr_assert(matrice_equals(m4, matrice_deserialize(matrice_serialize(m4, NULL))), "Matrices are not equal");
}

Test(matrices, test_csv_read_write) {
    setup();

    char *filename = "../_build/tests/TEMP_test_matrice.csv";
    char *message = "This file is used for testing matrice.c. It can be deleted.";

    matrice_to_csv(big1, filename, message);
    matrice *m = matrice_read_csv(filename);
    cr_assert(matrice_equals(m, big1), "Matrices are not equal");

    filename = "../_build/tests/TEMP_test_matrice2.csv";

    matrice_to_csv(big2, filename, message);
    m = matrice_read_csv(filename);
    cr_assert(matrice_equals(m, big2), "Matrices are not equal");

}
