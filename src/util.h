#ifndef HAAPA_UTIL_H
#define HAAPA_UTIL_H

#include "result.h" //for STRING_MAX_SIZE

typedef struct string {
    char data[STRING_MAX_SIZE];
    char replaced;
    int len;
    int pos;
    int dir;
} String;

char *jsonescape(const char *str);
char *jsonnescape(const char *str, int n);
int read_int(char *file_location, int *value, Result *res);
int read_string(char *file_location, char *value, Result *res);
char *string_get(String *str);
void string_udate_float(String *str, float value);
void string_update(String *str, char *new);

#endif
