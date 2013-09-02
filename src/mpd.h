#ifndef HAAPA_MPD_H
#define HAAPA_MPD_H

#include "result.h"

typedef struct mpd_response {
    int err;
    union {
        struct {
            int playing; /* -1 stopped, 1 paused, 0 playing */

            int vera, verb, verc; /* version numbers */
            int repeat; /* 0 repeat off, 1 repeat on */
            int qv; /* queue version */
            int ql; /* queue length */
            int spos; /* song position in playlist */
            int sels; /* song position in seconds */
            int selms; /* song position in ms */
            int slen; /* song length */
            int sbrate; /* song bit rate */

            int afsr; /* song sample rate */
            int afbits; /* song bit amount */
            int afchan; /* song channel amount */
        };
        int int_arr[15]; /* 7: spos, 8: sels, 9: selms */
    };
    int max_arr[15];
    union {
        struct {
            char const *uri; /* song URI */
            char const *artist; /* song artist */
            char const *album; /* song album */
            char const *title; /* song title */
            char const *track; /* song track */
            char const *name; /* song name */
            char const *date; /* song date */
        };
        char *char_arr[7];
    };
} mpd_response;

void _mpd_reset();
int _mpd_update();
int mpd_playing();
Result *_mpd_wrap(int i);
Result *_mpd_swrap(int i);
Result *mpd_smart(char *sep);

/* use mpd_vera for example */
#define M(a) Result *mpd_ ##a();
M(vera)
M(verb)
M(verc)
M(qv)
M(ql)
M(spos)
M(sels)
M(selms)
M(slen)
M(sbrate)
M(afsr)
M(afbits)
M(afchan)
M(uri)
M(artist)
M(album)
M(title)
M(track)
M(name)
M(date)
#undef M
#endif
