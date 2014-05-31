#include <stdlib.h>
#include <sys/vfs.h>
#include <stdio.h>
#include "fs.h"

struct statfs *fs_data = NULL;
fs_response *fsresponse = NULL;
static char *fs_cache;
static int fs_updated = 0;
void _fs_reset() {
    if (fs_updated) {
        fs_updated--;
    }
}
int _fs_update(char *path) {
    if (!fs_data) {
        fs_data = malloc(sizeof(struct statfs));
    }

    if (!fsresponse) {
        fsresponse = malloc(sizeof(fs_response));
    }

    if (statfs(path, fs_data)) {
        return -1;
    }

    fsresponse->total_space = fs_data->f_blocks * fs_data->f_bsize;
    fsresponse->free_space = fs_data->f_bavail * fs_data->f_bsize;
    fsresponse->used_space = fsresponse->total_space - fs_data->f_bsize *
                             fs_data->f_bfree;

    fs_updated = 15;
    return 0;
}

#define M() Result *res; \
    if(!fs_updated || path != fs_cache) \
        _fs_update(path);\
    res = init_res()

Result *fs_free(char *path) {
    M();
    sprintf(res->string, "%lu", fsresponse->free_space);
    res->value = fsresponse->free_space;
    res->max = fsresponse->total_space;
    return res;
}

Result *fs_used(char *path) {
    M();
    sprintf(res->string, "%lu", fsresponse->used_space);
    res->value = fsresponse->used_space;
    res->max = fsresponse->total_space;
    return res;
}

Result *fs_total(char *path) {
    M();
    sprintf(res->string, "%lu", fsresponse->total_space);
    res->value = fsresponse->total_space;
    res->max = fsresponse->total_space;
    return res;
}
