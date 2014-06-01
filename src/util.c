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
