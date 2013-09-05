#ifndef HAAPA_FS_H
#define HAAPA_FS_H

#include "result.h"

typedef struct fs_response {
    union {
        struct {
            long total_space;
            long free_space;
            long used_space;
        };
        unsigned long long_max[4];
    };
    int fs_useless_var;
} fs_response;

void _fs_reset();
int _fs_update();
Result *fs_total(char *path);
Result *fs_free(char *path);
Result *fs_used(char *path);

#endif
