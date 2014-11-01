#ifndef HAAPA_RETURN_H
#define HAAPA_RETURN_H

#define STRING_MAX_SIZE 128

#include <time.h>

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
