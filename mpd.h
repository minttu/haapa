#ifndef __MPD_H_INCLUDED__
#define __MPD_H_INCLUDED__

int _mpd_status_init();
int _mpd_status_audio_format_init();
int _mpd_status_song_init();

/* normal functions */
void status_mpd_version(char *str);
void status_mpd_volume(char *str);
void status_mpd_repeat(char *str);
void status_mpd_queue_version(char *str);
void status_mpd_queue_length(char *str);
int status_mpd_is_playing();
void status_mpd_song_position_int(char *str);
void status_mpd_song_elapsed_second(char *str);
void status_mpd_song_elapsed_ms(char *str);
void status_mpd_song_length(char *str);
void status_mpd_song_bit_rate(char *str);

/* audio format functions */
void status_mpd_song_sample_rate(char *str);
void status_mpd_song_bits(char *str);
void status_mpd_song_channels(char *str);

/* song related functions */
void status_mpd_song_uri(char *str);
void status_mpd_song_artist(char *str);
void status_mpd_song_album(char *str);
void status_mpd_song_title(char *str);
void status_mpd_song_track(char *str);
void status_mpd_song_name(char *str);
void status_mpd_song_date(char *str);

void status_mpd_normal_wrap(char *str, void (*fp)(char *));
void status_mpd_audio_format_wrap(char *str, void (*fp)(char *));
void status_mpd_song_wrap(char *str, void (*fp)(char *));

#define MPD_VERS	status_mpd_normal_wrap(result, status_mpd_version); F
#define MPD_VOL		status_mpd_normal_wrap(result, status_mpd_volume); F
#define MPD_REP		status_mpd_normal_wrap(result, status_mpd_repeat); F
#define MPD_QV		status_mpd_normal_wrap(result, status_mpd_queue_version); F
#define MPD_QL		status_mpd_normal_wrap(result, status_mpd_queue_length); F
#define MPD_SPL		status_mpd_normal_wrap(result, status_mpd_song_position_int); F
#define MPD_SELSEC	status_mpd_normal_wrap(result, status_mpd_song_elapsed_second); F
#define MPD_SELMS	status_mpd_normal_wrap(result, status_mpd_song_elapsed_ms); F
#define MPD_SLEN	status_mpd_normal_wrap(result, status_mpd_song_length); F
#define MPD_SBR		status_mpd_normal_wrap(result, status_mpd_song_bit_rate); F

#define MPD_AFSR	status_mpd_audio_format_wrap(result, status_mpd_song_sample_rate); F
#define MPD_AFBITS	status_mpd_audio_format_wrap(result, status_mpd_song_bits); F
#define MPD_AFCHAN	status_mpd_audio_format_wrap(result, status_mpd_song_channels); F

#define MPD_URI		status_mpd_song_wrap(result, status_mpd_song_uri); F
#define MPD_ARTIST	status_mpd_song_wrap(result, status_mpd_song_artist); F
#define MPD_ALBUM	status_mpd_song_wrap(result, status_mpd_song_album); F
#define MPD_TITLE	status_mpd_song_wrap(result, status_mpd_song_title); F
#define MPD_TRACK	status_mpd_song_wrap(result, status_mpd_song_track); F
#define MPD_NAME	status_mpd_song_wrap(result, status_mpd_song_name); F
#define MPD_DATE	status_mpd_song_wrap(result, status_mpd_song_date); F

#endif /* __MPD_H_INCLUDED__ */
