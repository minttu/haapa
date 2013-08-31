#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <alsa/asoundlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "alsa.h"
#include "config.h"
#include "result.h"

Result *alsa_volume(char *str) {
	Result *res;
	res = init_res();

	snd_mixer_t *handle;
	snd_mixer_elem_t *elem;
	snd_mixer_selem_id_t *sid;

	char *mix_name = str;
	char *card = "default";
	int mix_index = 0;

	long vol = -1;
	long *outvol = &vol;

	snd_mixer_selem_id_alloca(&sid);

	snd_mixer_selem_id_set_index(sid, mix_index);
	snd_mixer_selem_id_set_name(sid, mix_name);

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);
	elem = snd_mixer_find_selem(handle, sid);

	long minv, maxv;

	snd_mixer_selem_get_playback_volume_range (elem, &minv, &maxv);

	snd_mixer_selem_get_playback_volume(elem, 0, outvol);

	*outvol -= minv;
	maxv -= minv;
	minv = 0;

	res->value = *outvol;
	res->max = maxv;

	snd_mixer_close(handle);

	return res;
}

int alsa_muted(char *str) {
	snd_mixer_t *handle;
	snd_mixer_selem_id_t *sid;
	snd_mixer_elem_t *elem;
	char *card = "default";
	char *selem_name = str;
	int val = -1;

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, selem_name);
	elem = snd_mixer_find_selem(handle, sid);

	snd_mixer_selem_get_playback_switch(elem, 0, &val);

	snd_mixer_close(handle);
	return !val;
}

int alsa_nmuted(char *str) {
	return !alsa_muted(str);
}
