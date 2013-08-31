#ifndef HAAPA_ALSA_H
#define HAAPA_ALSA_H

#include "result.h"

Result* alsa_volume(char* str);
int alsa_muted(char* str);
int alsa_nmuted(char* str);

#endif
