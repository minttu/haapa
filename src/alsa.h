#ifndef HAAPA_ALSA_H
#define HAAPA_ALSA_H

#include "result.h"

typedef struct alsa_response {
    int err;
    union {
        struct {
            long minvol;
            long maxvol;
            long volume;
            int unmuted;
        };
        long int_arr[4];
    };
    long max_arr[4];
} alsa_response;

void _alsa_reset();
int _alsa_update();
Result *alsa_volume(char *str);
int alsa_muted(char *str);
int alsa_nmuted(char *str);

#endif
