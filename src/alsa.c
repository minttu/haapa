#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "alsa.h"
#include "config.h"
#include "result.h"

alsa_response *als_response;
int mix_index = 0, i;
char *card = "default";
static int alsa_updated = 0;
snd_mixer_t *handle;
snd_mixer_elem_t *elem;
snd_mixer_selem_id_t *sid = NULL;

void _alsa_reset() {
    alsa_updated = 0;
}

int _alsa_update() {
    int i;
    const char *mix_name = alsa_channel;

    if(!als_response) {
        als_response = calloc(sizeof(alsa_response), 1);
        for(i = 0; i < 4; i++)
            als_response->max_arr[i] = 1;
    }

  	snd_mixer_selem_id_alloca(&sid);
   	snd_mixer_selem_id_set_index(sid, mix_index);
    snd_mixer_selem_id_set_name(sid, mix_name);

    snd_mixer_open(&handle, 0);
   	snd_mixer_attach(handle, card);
   	snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);
    elem = snd_mixer_find_selem(handle, sid);

    if(!elem) {
        snd_mixer_close(handle);
        return -1;
    }

    snd_mixer_selem_get_playback_volume_range (elem, &(als_response->minvol), &(als_response->maxvol));
    snd_mixer_selem_get_playback_volume(elem, 0, &(als_response->volume));
    snd_mixer_selem_get_playback_switch(elem, 0, &(als_response->unmuted));

    snd_mixer_close(handle);
    sid = 0;

	als_response->volume -= als_response->minvol;
	als_response->maxvol -= als_response->minvol;
	als_response->minvol = 0;

    als_response->max_arr[0] = als_response->maxvol;
    als_response->max_arr[1] = als_response->maxvol;
    als_response->max_arr[2] = als_response->maxvol;
    alsa_updated = 1;

    return 0;
}

int alsa_muted(char *str) {
    if(!alsa_updated)
        _alsa_update();
    if(als_response)
        return !als_response->unmuted;
    return 1;
}

int alsa_nmuted(char *str) {
	return !alsa_muted(str);
}

Result *_alsa_wrap(int i) {
    Result *res = init_res();
    if(!alsa_updated)
        _alsa_update();
    res->value = als_response->int_arr[i];
    res->max = als_response->max_arr[i];
    sprintf(res->string, "%ld", als_response->int_arr[i]);
    return res;
}

#define M(a, b) Result *alsa_ ##a(char *str) { \
    return _alsa_wrap(b); \
}
M(minvol, 0)
M(maxvol, 1)
M(volume, 2)
#undef M
