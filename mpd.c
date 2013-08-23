#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpd/client.h>

#include "mpd.h"
#include "config.h"

struct mpd_connection *conn;
struct mpd_status *status;
struct mpd_song *song;
struct mpd_audio_format *audio_format;

/* do not call */
int _mpd_status_init() {
    if(!conn)
        conn = mpd_connection_new(NULL, 0, 30000);
    if(mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS) {
        fprintf(stderr, "connection: %s\n", mpd_connection_get_error_message(conn));
        if(conn)
            mpd_connection_free(conn);
        return -1;
    }
    mpd_command_list_begin(conn, 1);
    mpd_send_status(conn);
    mpd_send_current_song(conn);
    mpd_command_list_end(conn);
    status = mpd_recv_status(conn);
    if(status == NULL) {
        printf("asd\n");
        fprintf(stderr, "status: %s\n", mpd_connection_get_error_message(conn));
        if(conn)
            mpd_connection_free(conn);
        return -1;
    }
    return 0;
}

/* do not call */
int _mpd_status_audio_format_init() {
    struct mpd_audio_format const *format;
    format = mpd_status_get_audio_format(status);
    if(!format) return -1;
    memcpy(audio_format, format, sizeof(struct mpd_audio_format));
    return 0;
}

/* do not call */
int _mpd_status_song_init() {
    song = mpd_recv_song(conn);
    if(!song) return -1;
    return 0;
}


/* mpd version as x.yy.zz */
void status_mpd_version(char *str) {
    unsigned int const *arr;
    char buf[SEGMENT_LENGTH];
    char itoabuf[33];
    arr = mpd_connection_get_server_version(conn);
    sprintf(itoabuf, "%d", arr[0]);
    strncat(buf, itoabuf, SEGMENT_LENGTH-1);
    strcat(buf, ".\0");
    sprintf(itoabuf, "%d", arr[0]);
    strncat(buf, itoabuf, SEGMENT_LENGTH-strlen(buf)-1);
    strcat(buf, ".\0");
    sprintf(itoabuf, "%d", arr[0]);
    strncat(buf, itoabuf, SEGMENT_LENGTH-strlen(buf)-1);
    strncpy(str, buf, SEGMENT_LENGTH);
}

/* volume */
void status_mpd_volume(char *str) {
    int val;
    char itoabuf[33];
    itoabuf[0] = 0;
    val = mpd_status_get_volume(status);
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* repeat */
void status_mpd_repeat(char *str) {
    int val;
    char itoabuf[33];
    val = mpd_status_get_repeat(status);
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* queue version */
void status_mpd_queue_version(char *str) {
    unsigned int val;
    char itoabuf[33];
    val = mpd_status_get_queue_version(status);
    sprintf(itoabuf, "%u", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* queue length */
void status_mpd_queue_length(char *str) {
    int val;
    char itoabuf[33];
    val = mpd_status_get_queue_length(status);
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* returns 0 if stopped or error, -1 if stopped and 1 if playing */
int status_mpd_is_playing() {
    int val;
    val = mpd_status_get_state(status);
    if(val == MPD_STATE_PLAY) return 1;
    else if(val == MPD_STATE_PAUSE) return -1;
    return 0;
}

/* current song as position on playlist */
void status_mpd_song_position_int(char *str) {
    int val;
    char itoabuf[33];
    val = mpd_status_get_song_pos(status);
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* elapsed time as seconds */
void status_mpd_song_elapsed_second(char *str) {
    int val;
    char itoabuf[33];
    val = mpd_status_get_elapsed_time(status);
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* elapsed time as ms */
void status_mpd_song_elapsed_ms(char *str) {
    int val;
    char itoabuf[33];
    val = mpd_status_get_elapsed_ms(status);
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* current song length as seconds */
void status_mpd_song_length(char *str) {
    int val;
    char itoabuf[33];
    val = mpd_status_get_total_time(status);
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* current song bit rate as kbit */
void status_mpd_song_bit_rate(char *str) {
    int val;
    char itoabuf[33];
    val = mpd_status_get_kbit_rate(status);
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* current song sample rate */
void status_mpd_song_sample_rate(char *str) {
    int val;
    char itoabuf[33];
    val = audio_format->sample_rate;
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* current song bits */
void status_mpd_song_bits(char *str) {
    int val;
    char itoabuf[33];
    val = audio_format->bits;
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* current song channels */
void status_mpd_song_channels(char *str) {
    int val;
    char itoabuf[33];
    memcpy(&val, &audio_format->channels, sizeof(int));
    sprintf(itoabuf, "%d", val);
    strncat(str, itoabuf, SEGMENT_LENGTH);
}

/* current song uri */
void status_mpd_song_uri(char *str) {
    printf("moi");
    char const *val;
    val = mpd_song_get_uri(song);
    if(!val) return;
    strncat(str, val, SEGMENT_LENGTH);
}

/* current song artist */
void status_mpd_song_artist(char *str) {
    char const *val;
    val = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
    if(!val) return;
    strncat(str, val, SEGMENT_LENGTH);
}

/* current song album */
void status_mpd_song_album(char *str) {
    char const *val;
    val = mpd_song_get_tag(song, MPD_TAG_ALBUM, 0);
    if(!val) return;
    strncat(str, val, SEGMENT_LENGTH);
}

/* current song title */
void status_mpd_song_title(char *str) {
    char const *val;
    val = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
    if(!val) return;
    strncat(str, val, SEGMENT_LENGTH);
}

/* current song track */
void status_mpd_song_track(char *str) {
    char const *val;
    val = mpd_song_get_tag(song, MPD_TAG_TRACK, 0);
    if(!val) return;
    strncat(str, val, SEGMENT_LENGTH);
}

/* current song name */
void status_mpd_song_name(char *str) {
    char const *val;
    val = mpd_song_get_tag(song, MPD_TAG_NAME, 0);
    if(!val) return;
    strncat(str, val, SEGMENT_LENGTH);
}

/* current song date */
void status_mpd_song_date(char *str) {
    char const *val;
    val = mpd_song_get_tag(song, MPD_TAG_DATE, 0);
    if(!val) return;
    strncat(str, val, SEGMENT_LENGTH);
}

/* call a "normal" mpd function */
void status_mpd_normal_wrap(char *str, void (*fp)(char *)) {
    if(_mpd_status_init()) return;
    str[0] = 0;
    fp(str);
    mpd_response_finish(conn);
}

/* call an audio format related mpd function */
void status_mpd_audio_format_wrap(char *str, void (*fp)(char *)) {
    if(_mpd_status_init() || _mpd_status_audio_format_init()) return;
    str[0] = 0;
    fp(str);
    mpd_response_finish(conn);
}

/* call an song related mpd function */
void status_mpd_song_wrap(char *str, void (*fp)(char *)) {
    str[0] = 0;
    if(_mpd_status_init() || _mpd_status_song_init()) return;
    fp(str);
    mpd_response_finish(conn);
    song = NULL;
}
