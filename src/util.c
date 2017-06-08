#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "config.h"
#include "util.h"

char *jsonescape(const char *str) {
    return jsonnescape(str, 0);
}

char *jsonnescape(const char *str, int n) {
    int i = 0, h = 0, j;
    char *ret;

    if (!str) {
        return NULL;
    }

    while (str[i] != 0) {
        if (n && i >= n) {
            break;
        }

        if (str[i] == '"' || str[i] == '\\') {
            h++;
        }

        i++;
    }

    ret = malloc(i + h + 1);

    for (h = 0, j = 0; j < i; j++) {
        if (formatter == format_i3 && (str[j] == '"' || str[j] == '\\')) {
            ret[j + h++] = '\\';
        }

        ret[j + h] = str[j];
    }

    ret[j + h] = 0;
    return ret;
}

int read_int(char *file_location, int *value, Result *res) {
    FILE *f;
    int ret;

    f = fopen(file_location, "r");

    if (f == NULL) {
        res->error = 1;
        return 0;
    }

    ret = fscanf(f, "%i", value);
    fclose(f);

    if (ret == EOF) {
        res->error = 1;
        return 0;
    }

    return 1;
}

int read_string(char *file_location, char *value, Result *res) {
    FILE *f;
    int ret;

    f = fopen(file_location, "r");

    if (f == NULL) {
        res->error = 1;
        return 0;
    }

    ret = fscanf(f, "%s", value);
    fclose(f);

    if (ret == EOF) {
        res->error = 1;
        return 0;
    }

    return 1;
}

char *string_get(String *str) {
    return str->data + str->pos;
}

void string_update_float(String *str, float value) {
    char buf[STRING_MAX_SIZE];
    snprintf(buf, sizeof(buf), "%f", value);
    string_update(str, buf);
}

static char string_set_value(char *target, char value, size_t length) {
    int i, j;
    for (i = 0, j = -1;; i++) {
        if ((target[i] & 0xc0) != 0x80) j++;

        if(j == length) {
            char old = target[i];
            target[i] = value;
            return old;
        }
    }
    return 0;
}

static size_t string_length(char *source) {
    size_t j;
    int i;
    for (i = 0, j = 0; source[i]; i++) {
        if ((source[i] & 0xc0) != 0x80) j++;
    }
    return j;
}

void string_update(String *str, char *new) {
    if (str->len) {
        str->replaced = string_set_value(str->data, str->replaced, str->pos + str_max_length);
    }

    if (!strcmp(str->data, new)) {
        if (str_max_length && str->len > str_max_length) {
            str->pos += str->dir;

            if (str->pos < 0) {
                str->pos = 0;
                str->dir = 1;
            } else if (str->pos > str->len - str_max_length) {
                str->pos = str->len - str_max_length;
                str->dir = -1;
            }

            str->replaced = string_set_value(str->data, 0,
                    str->pos + str_max_length);
        }

        return;
    }

    strcpy(str->data, new);

    str->len = string_length(new);
    str->pos = 0;
    str->replaced = 0;

    if (str_max_length && str->len > str_max_length) {
        str->replaced = string_set_value(str->data, 0, str_max_length);
    }
}
