#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "alsa.h"
#include "config.h"
#include "result.h"

alsa_response *response;
int mix_index = 0, i;
char *card = "default";
snd_mixer_t *handle;
snd_mixer_elem_t *elem;
snd_mixer_selem_id_t *sid = NULL;

int _alsa_update() {
    int i;
    const char *mix_name = alsa_channel;

    if(!response) {
        response = calloc(sizeof(response), 1);
        for(i = 0; i < 4; i++)
            response->max_arr[i] = 1;
    }
    if(!sid) {
    	snd_mixer_selem_id_alloca(&sid);

    	snd_mixer_selem_id_set_index(sid, mix_index);
	    snd_mixer_selem_id_set_name(sid, mix_name);

	    snd_mixer_open(&handle, 0);
        snd_config_update_free_global();
    	snd_mixer_attach(handle, card);
    	snd_mixer_selem_register(handle, NULL, NULL);
	    snd_mixer_load(handle);
	    elem = snd_mixer_find_selem(handle, sid);
    }
    snd_mixer_selem_get_playback_volume_range (elem, &(response->minvol), &(response->maxvol));
    snd_mixer_selem_get_playback_volume(elem, 0, &(response->volume));
    snd_mixer_selem_get_playback_switch(elem, 0, &(response->unmuted));


	response->volume -= response->minvol;
	response->maxvol -= response->minvol;
	response->minvol = 0;

    response->max_arr[0] = response->maxvol;
    response->max_arr[1] = response->maxvol;
    response->max_arr[2] = response->maxvol;

    return 0;
}

int alsa_muted(char *str) {
    return !response->unmuted;
}

int alsa_nmuted(char *str) {
	return !alsa_muted(str);
}

Result *_alsa_wrap(int i) {
    Result *res = init_res();
    res->value = response->int_arr[i];
    res->max = response->max_arr[i];
    sprintf(res->string, "%ld", response->int_arr[i]);
    return res;
}

#define M(a, b) Result *alsa_ ##a(char *str) { \
    return _alsa_wrap(b); \
}
M(minvol, 0)
M(maxvol, 1)
M(volume, 2)
#undef M
