#include "params.h"

const char *skipdir(const char *path)
{
  const char *p = path + strlen(path);
  while (p > path && *p != '/') p--;
  return p + 1;
}

Params get_params(const char *filename)
{
    Params p = {
        .ff_c = 1,
        .b_th = 125,
    };

    int i = *skipdir(filename) - '0';
    switch (i) {
        case 2:
            p.ff_c = 6;
    }
    return p;
}
