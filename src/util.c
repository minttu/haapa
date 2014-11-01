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

void string_update(String *str, char *new) {
    if(str->len)
        str->data[str->pos + str_max_length] = str->replaced;
    if(!strcmp(str->data, new)) {
        if(str_max_length && str->len > str_max_length) {
            str->data[str->pos + str_max_length] = str->replaced;
            str->pos += str->dir;
            str->replaced = str->data[str->pos + str_max_length];
            str->data[str->pos + str_max_length] = 0;
            if(str->pos + str_max_length >= str->len)
                str->dir = -1;
            if(str->pos == 0)
                str->dir = 1;
        }
        return;
    }
    memcpy(str->data, new, STRING_MAX_SIZE);
    str->len = strlen(str->data);
    if(str->len)
        str->replaced = str->data[0];
    str->pos = 0;
    if(str_max_length && str->len > str_max_length) {
        str->replaced = str->data[str_max_length];
        str->data[str_max_length] = 0;
    }
}
