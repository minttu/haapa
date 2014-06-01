#ifndef HAAPA_UTIL_H
#define HAAPA_UTIL_H

char *jsonescape(const char *str);
char *jsonnescape(const char *str, int n);
int read_int(char *file_location, int *value, Result *res);
int read_string(char *file_location, char *value, Result *res);

#endif
