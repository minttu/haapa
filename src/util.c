#include <stdlib.h>

#include "config.h"
#include "util.h"

char *jsonescape(const char *str) {
    return jsonnescape(str, 0);
}

char *jsonnescape(const char *str, int n) {
    int i = 0, h = 0, j;
    char *ret;
    if(!str)
        return NULL;
    while(str[i] != 0) {
        if(n && i >= n)
            break;
        if(str[i] == '"' || str[i] == '\\')
            h++;
        i++;
    }
    ret = malloc(i + h);
    for(h = 0, j = 0; j < i; j++) {
        if(formatter == format_i3 && (str[j] == '"' || str[j] == '\\'))
            ret[j + h++] = '\\';
        ret[j + h] = str[j];
    }
    ret[j + h] = 0;
    return ret;
}
