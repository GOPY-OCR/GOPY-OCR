#pragma once
#include "file_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

char *float_to_string(float d);

void write_to_file(char *filename, char *data);

char *read_from_file(char *filename);
