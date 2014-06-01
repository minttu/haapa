#ifndef HAAPA_RETURN_H
#define HAAPA_RETURN_H

#include <time.h>

typedef struct {
    char string[128];
    float value;
    float max;
    time_t time_value;
    int status;
    int error;
    int hidden;
} Result;

Result *init_res();

#endif
