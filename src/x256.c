#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "x256.h"

typedef struct {
    int r;
    int g;
    int b;
} Color;

typedef struct {
    char *str;
    int index;
} CachedColor;

CachedColor cache[64];
int cache_size = 0;

Color _convert(int hex) {
    Color c;
    c.r = ((hex >> 16) & 0xFF);
    c.g = ((hex >> 8) & 0xFF);
    c.b = ((hex) & 0xFF);
    return c;
}

double _dist(Color a, Color b) {
    double x, y, z;
    x = pow(a.r - b.r, 2);
    y = pow(a.g - b.g, 2);
    z = pow(a.b - b.b, 2);
    return sqrt(x + y + z);
}

char *_strip(char *str) {
    if(str[0] == '#')
        str++;
    return str;
}

int get_cached(char *str) {
    int i;
    for(i = 0; i < cache_size; i++) {
        if(strcmp(str, cache[i].str)==0) {
            return cache[i].index;
        }
    }
    return -1;
}

void add_cached(char *str, int index) {
    if(get_cached(str)==-1) {
        cache[cache_size].str = str;
        cache[cache_size].index = index;
        cache_size++;
    }
}

int get_x256(char *str) {
    int i;
    char *target = _strip(str);
    Color target_color;
    Color tmp_color;
    int best = -1;
    double tmp_val = -1;
    double best_val = 999999.0;

    i = get_cached(target);
    if(i!=-1)
        return i;
    i = 0;

    target_color = _convert((int)strtol(target, NULL, 16));

    for(i = 16; i < 256; i++) {
        if(strcmp(colors[i],target)==0) {
            best = i;
            break;
        }
        tmp_color = _convert((int)strtol(colors[i], NULL, 16));
        tmp_val = _dist(target_color, tmp_color);
        if(tmp_val<best_val) {
            best_val = tmp_val;
            best = i;
        }
    }

    add_cached(target, best);

    return best;
}