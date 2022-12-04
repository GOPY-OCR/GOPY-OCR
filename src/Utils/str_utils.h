#pragma once
#include "file_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

char *double_to_string(double d);

void write_to_file(char *filename, char *data);

char *read_from_file(char *filename);


char *serialize_double(double f);
