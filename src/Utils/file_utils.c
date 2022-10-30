#include "file_utils.h"


int file_exists(const char *filename){
    return access(filename, F_OK) == 0;
}
