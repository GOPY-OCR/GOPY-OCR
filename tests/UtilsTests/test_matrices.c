#include "matrice.h"

matrice *m1, *m2, *m3, *m4, *m5, *big1, *big2, *weird;
char *serialized_big1, *serialized_m1;

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
    m5 = matrice_from_string("1 2 3,"
                             "4 5 6,"
                             "7 2 9");

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
    serialized_m1 = "2x2\n"
                    "1;2\n"
                    "3;4\n";

    big2 = matrice_from_string("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41");

    weird = matrice_from_string("1234567891000000002,"
                                "0.00000000000000000000000000001");
}

void assert_matrices_equals(matrice *m1, matrice *m2) {
    int eq = matrice_equals(m1, m2);
    char *s1 = matrice_serialize(m1, "m1");
    char *s2 = matrice_serialize(m2, "m2");
    cr_assert(eq, "%sis not equal to\n%s", s1, s2);
}

#define MATRICE_EPSILON 0.000002
void assert_matrices_almost_equals(matrice *m1, matrice *m2) {
    int eq = matrice_equals_epsilon(m1, m2, MATRICE_EPSILON);
    char *s1 = matrice_serialize(m1, "m1");
    char *s2 = matrice_serialize(m2, "m2");
    cr_assert(eq, "%sis not almost equal to\n%s(epsilon = %f)", s1, s2, MATRICE_EPSILON);
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

    assert_matrices_equals(m, expected);
}

Test(matrice, test_sub) {
    setup();

    matrice *expected = matrice_from_string("-4 -4,"
            "-4 -4");
    matrice *m = matrice_sub(m1, m2);

    assert_matrices_equals(m, expected);
}

Test(matrice, test_mul) {
    setup();

    matrice *expected = matrice_from_string("5 12,"
            "21 32");

    matrice *m = matrice_mul(m1, m2);

    assert_matrices_equals(m, expected);
}

Test(matrices, test_dot) {
    setup();

    matrice *expected = matrice_from_string("19 22,"
            "43 50");
    matrice *m = matrice_dot(m1, m2);

    assert_matrices_equals(m, expected);
}

Test(matrices, test_transpose) {
    setup();

    matrice *expected = matrice_from_string("1 3,"
            "2 4");
    matrice *m = matrice_transpose(m1);

    assert_matrices_equals(m, expected);
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

    assert_matrices_equals(m1, expected);
}

double multiply_by_two(double x) { return x * 2; }

Test(matrices, test_map) {
    setup();

    matrice *expected = matrice_from_string("2 4,"
            "6 8");
    matrice_map(m1, multiply_by_two);

    assert_matrices_equals(m1, expected);
}

Test(matrices, test_add_inplace) {
    setup();

    matrice *expected = matrice_from_string("6 8,"
                                            "10 12");
    matrice_add_inplace(m1, m2);

    cr_assert(matrice_equals(m1, expected), "Matrices are not equal");
}


Test(matrices, test_clone) {
    setup();

    matrice *m = matrice_clone(m1);

    assert_matrices_equals(m, m1);

    // Free m1 and check if m is still the same
    matrice_free(m1);
    setup();
    assert_matrices_equals(m, m1);
}

Test(matrices, test_clone_harder) {
    setup();

    matrice *copy1 = matrice_clone(big1);
    matrice *copy2 = matrice_clone(big1);

    assert_matrices_equals(copy1, copy2);

    // Free big1 and check if copy1 and copy2 are still the same
    matrice_free(big1);
    assert_matrices_equals(copy1, copy2);

    matrice_free(matrice_clone(copy1));
    matrice_free(matrice_clone(copy2));
    // nothings should have changed
    assert_matrices_equals(copy1, copy2);
}

Test(matrices, test_max) {
    setup();

    int i;
    int j;

    double *max = matrice_max(m1, &i, &j);

    cr_assert(i == 1 && j == 1, "Max is not in the right place");
    cr_assert(*max == 4, "Max is not equal to 4");
}

Test(matrices, test_max_dont_modify) {
    setup();

    matrice *copy = matrice_clone(m1);

    int i,j;

    matrice_max(m1, &i, &j);

    cr_assert(matrice_equals(m1, copy), "Max modified the matrix (m1)");

    copy = matrice_clone(big1);

    matrice_max(big1, &i, &j);

    cr_assert(matrice_equals(big1, copy), "Max modified the matrix (big1)");
}

Test(matrices, test_max_no_index) {
    setup();

    // sometimes we don't need the index of the max
    // value, so we should be able to pass NULL
    // as the index parameters

    double *max = matrice_max(m1, NULL, NULL);

    cr_assert(*max == 4, "Max is not equal to 4");
}

Test(matrices, test_sum) {
    setup();

    double sum = matrice_sum(m1);

    cr_assert(sum == 10, "Sum is not equal to 10");
}

Test(matrices, test_mean){
    setup();

    double mean = matrice_mean(m1);

    cr_assert(mean == 2.5, "Mean is not equal to 2.5");
}

Test(matrices, test_std){
    setup();

    double std = matrice_std(m1);

    cr_assert(std == 1.118033988749895, "Std is not equal to 1.118033988749895");
}



Test(matrices, test_serialize) {
    setup();

    cr_assert_str_eq(matrice_serialize(m1, "m1"), "# m1\n"
                                                  "2x2\n"
                                                  "1;2\n"
                                                  "3;4\n");

    cr_assert_str_eq(matrice_serialize(m1, NULL), serialized_m1);

    cr_assert_str_eq(matrice_serialize(big1, "big1"), serialized_big1);
}

Test(matrices, test_deserialize) {
    setup();

    matrice *m = matrice_deserialize(serialized_big1, NULL);

    assert_matrices_almost_equals(m, big1);

    assert_matrices_almost_equals(m1, matrice_deserialize(matrice_serialize(m1, NULL), NULL));
    assert_matrices_almost_equals(m2, matrice_deserialize(matrice_serialize(m2, NULL), NULL));
    assert_matrices_almost_equals(m3, matrice_deserialize(matrice_serialize(m3, NULL), NULL));
    assert_matrices_almost_equals(m4, matrice_deserialize(matrice_serialize(m4, NULL), NULL));
    //assert_matrices_almost_equals(weird, matrice_deserialize(matrice_serialize(weird, "weird"), NULL));


    char *ptr = NULL;
    m = matrice_deserialize(serialized_m1, &ptr);
    int len = strlen(serialized_m1);
    cr_assert(ptr - serialized_m1 == len, "Pointer is not at the end of the string");
}

Test(matrices, test_csv_read_write) {
    setup();

    char *filename = "../_build/tests/TEMP_test_matrice.csv";
    char *message = "This file is used for testing matrice.c. It can be deleted.";

    matrice_to_csv(big1, filename, message);
    matrice *m = matrice_read_csv(filename);
    assert_matrices_almost_equals(m, big1);

    filename = "../_build/tests/TEMP_test_matrice2.csv";

    matrice_to_csv(big2, filename, message);
    m = matrice_read_csv(filename);
    assert_matrices_equals(m, big2);
}

Test(matrices, test_matrice_invert){
    setup();

    matrice *m = matrice_from_string("4 7,"
                                     "2 6");
    matrice *expected = matrice_from_string("0.6 -0.7,"
                                            "-0.2 0.4");
    matrice *result = matrice_invert(m);
    assert_matrices_almost_equals(result, expected);


    matrice *m1inv = matrice_from_string("-2 1,"
                                         "1.5 -0.5");
    result = matrice_invert(m1);
    assert_matrices_almost_equals(result, m1inv);

    matrice *m5inv = matrice_from_string("-0.91666667 0.33333333 0.083333333,"
                                         "-0.16666667 0.33333333 -0.16666667,"
                                         "0.750000000 -0.33333333 0.083333333");
    result = matrice_invert(m5);
    assert_matrices_almost_equals(result, m5inv);

    

    result = matrice_invert(matrice_invert(m));
    assert_matrices_almost_equals(result, m);

    result = matrice_invert(matrice_invert(m1));
    assert_matrices_almost_equals(result, m1);

    result = matrice_invert(matrice_invert(m5));
    assert_matrices_almost_equals(result, m5);
}
