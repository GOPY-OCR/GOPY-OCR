#include "str_utils.h"

Test(str_utils, test_double_to_string){
    char *s[4] = 
    {
        "0.0001",
        "123456789.123456",
        "42.000042",
        "1",
    };

    for(int i = 0; i < 4; i++){
        char *str = double_to_string(atof(s[i]));
        cr_assert(strcmp(str, s[i]) == 0, "Expected %s, got %s", s[i], str);
        free(str);
    }
}
