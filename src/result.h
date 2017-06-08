#ifndef HAAPA_RETURN_H
#define HAAPA_RETURN_H

#include <time.h>

#define STRING_MAX_SIZE 512

typedef struct result {
    char string[STRING_MAX_SIZE];
    float value;
    float max;
    time_t time_value;
    int status;
    int error;
    int hidden;
} Result;

Result *init_res();

#endif
