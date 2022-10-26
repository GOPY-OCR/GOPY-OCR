#include "progress_bar.h"

void progress_bar(int bar_size, int completed, int total, char *name){

    char *bar = malloc(bar_size + strlen(name) + 30);
    int nb = (completed * bar_size) / total;
    int i = 0;
    bar[i++] = '[';
    for(; i <= nb; i++){
        bar[i] = '=';
    }
    for(; i < bar_size; i++){
        bar[i] = ' ';
    }
    bar[i++] = ']';
    bar[i++] = ' ';
    i += sprintf(bar + i, "%d/%d", completed, total);
    bar[i++] = ' ';
    i += sprintf(bar + i, "%s", name);

    printf("%s\r", bar);
}
