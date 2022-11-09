#include "file_utils.h"
#include <criterion/criterion.h>


Test(test_file_utils, test_file_exists)
{
    char *file = "UtilsTests/test_file_utils.c";
    int exists = file_exists(file);
    cr_assert(file_exists(file) == 1);

    file = "UtilsTests/test_file_utils.h";
    cr_assert(file_exists(file) == 0);
}

Test(test_file_utils, test_dir_exists)
{
    char *dir = "UtilsTests";
    cr_assert(dir_exists(dir) == 1);

    dir = "UtilsTests/";
    cr_assert(dir_exists(dir) == 1);

    dir = "UtilsTests/test_file_utils.c";
    cr_assert(dir_exists(dir) == 0);
}

Test(test_file_utils, test_copy_file)
{
    char *src = "UtilsTests/test_file_utils.c";
    char *dest = "../_build/tests/UtilsTests/test_file_utils_COPY.c";

    cr_assert(file_exists(dest) == 0);

    copy_file(src, dest);

    cr_assert(file_exists(dest) == 1);
}

Test(test_file_utils, test_delete_dir_recursive)
{
    char *dir = "../_build/tests/UtilsTests/TEST_DIR";
    char *subdir = "../_build/tests/UtilsTests/TEST_DIR/TEST_SUBDIR";
    char *src = "UtilsTests/test_file_utils.c";
    char *dest = "../_build/tests/UtilsTests/TEST_DIR/TEST_SUBDIR/test_file_utils.c";

    // create the folder
    mkdir(dir, 0777);

    cr_assert(dir_exists(dir) == 1);

    // create a subfolder
    mkdir(subdir, 0777);

    cr_assert(dir_exists(subdir) == 1);

    // copy a file inside the subfolder
    copy_file(src, dest);

    cr_assert(file_exists(dest) == 1);

    // delete the folder
    delete_dir_recursive(dir); 

    cr_assert(dir_exists(dir) == 0);
}
