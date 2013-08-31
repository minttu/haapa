#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <event.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <stdbool.h>

#include "haapa.h"
#include "config.h"
#include "result.h"
#include "proc.h"
#include "time.h"
#include "battery.h"
#include "network.h"

#ifdef INCLUDE_IWLIB
#include "wireless.h"
#endif
#ifdef INCLUDE_MPD
#include "mpd.h"
#endif

char buffer[1024];

static const char *optString = "hov?";

struct arguments_t {
	int once;
} arguments;

static const struct option longOpts[] = {
	{ "once", no_argument, NULL, 'o' },
	{ "version", no_argument, NULL, 'v' },
	{ "help", no_argument, NULL, 'h' },
	{ NULL, no_argument, NULL, 0 }
};

void start_segment() {
	if(output_format == FORMAT_I3)
		strcat(buffer, ",{\"full_text\": \"");
}

void end_segment(char *color) {
	if(output_format == FORMAT_I3){
		char colorbuffer[64];
		colorbuffer[0] = 0;
		sprintf(colorbuffer, "\", \"color\": \"%s\"}\n", color);
		strcat(buffer, colorbuffer);
	}else{
		strcat(buffer, " ");
	}
}

void string(Result *(*function)(char *str), char *str) {
	Result *res = function(str);
	if(res->error) {
		free(res);
		strcat(buffer, "error");
		return;
	}
	strcat(buffer, res->string);
	free(res);
}

Result *text(char *str) {
	Result *res = init_res();
	strcpy(res->string, str);
	return res;
}

void bar(Result *(*function)(char *str), char *str) {
	Result *res = function(str);
	char bar[11];
	char buffbar[13];
	int i;
	float value;
	float tmp_val;
	if(res->error) {
		free(res);
		strcat(buffer, "error");
		return;
	}

	value = (res->value / res->max)*10;
	tmp_val = round(value);

	bar[0] = 0;

	for(i = 0; i < 10; i++) {
		if(i < tmp_val) {
			strcat(bar, "#");
		}else{
			strcat(bar, "_");
		}
	}

	sprintf(buffbar, "[%s]", bar);
	strcat(buffer, buffbar);
	free(res);
}

void percent(Result *(*function)(char *str), char *str) {
	Result *res = function(str);
	char per[5];
	per[0] = 0;
	if(res->error) {
		free(res);
		strcat(buffer, "error");
		return;
	}
	sprintf(per, "%i%%", (int)round((res->value/res->max)*100));
	strcat(buffer, per);
	free(res);
}

void timeconv(Result *(*function)(char *str), char *str) {
    Result *res = function(str);
    char buf[128];
    buf[0] = 0;
    int w, d, h, m, s;
    if(res->error) {
        free(res);
        strcat(buffer, "error");
        return;
    }
    w = ((int)res->value/(60*60*24*7));
    d = ((int)res->value/(60*60*24))%24;
    h = ((int)res->value/(60*60))%60;
    m = ((int)res->value/60)%60;
    s = ((int)res->value)%60;
    if(w)
        snprintf(buf, sizeof(buf), "%d weeks %d days %02dh %02dm %02ds", w, d, h, m, s);
    else if(d)
        snprintf(buf, sizeof(buf), "%d days %02dh %02dm %02ds", d, h, m, s);
    else if(h)
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d", h, m, s);
    else
        snprintf(buf, sizeof(buf), "%02d:%02d", m, s);
    strcat(buffer, buf);
}

int always(char *str) {
	return 1;
}

int never(char *str) {
	return 0;
}

void tick(int fd, short event, void *arg) {

	int i;

#ifdef INCLUDE_MPD
	_mpd_update();
#endif

	buffer[0] = 0;

	if(output_format == FORMAT_I3)
		strcat(buffer, "[{\"full_text\":\" \"}\n");

	for(i = 0; i < sizeof(segments)/sizeof(segments[0]); i++) {
		if(segments[i].condition_function(segments[i].condition_argument) == 1) {
			if(output_format == FORMAT_I3)
				start_segment();
			segments[i].output_function(segments[i].function, segments[i].function_argument);
			if(output_format == FORMAT_I3)
				end_segment(segments[i].color);
			strcat(buffer, segment_seperator);
		}
	}

	if(output_format == FORMAT_I3)
		strcat(buffer, "],");

	if(output_ontop == true) {
		printf("\r%s", buffer);
		fflush( stdout );
	}else {
		printf("%s\n", buffer);
		fflush( stdout );
	}

	if(arguments.once) {
		exit(0);
	}
}

void display_usage() {
	printf("usage: haapa [OPTION]\n");
	printf("  -h, --help      display this help and exit\n");
	printf("  -o, --once      runs output only once\n");
	printf("  -v, --version   display version information and exit\n");
	exit(0);
}

void display_version() {
	printf("haapa git\n");
	printf("Copyright (C) 2013 Haapa contributors\n");
	printf("License MIT\n");
	exit(0);
}

int main(int argc, char *const argv[]) {
	struct event ev;
	struct timeval tv;
	int opt;
	int longIndex = 0;

	arguments.once = 0;

	tv.tv_sec = interval;
	tv.tv_usec = 0;

	opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
	while( opt != -1 ) {
		switch( opt ) {
			case 'o':
				arguments.once++;
				break;

			case 'v':
				display_version();
				break;

			case 'h':
			case '?':
				display_usage();
				break;

			default: break;
		}

		opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
	}

	if(output_format == FORMAT_I3) {
		printf("{\"version\":1}\n[[{\"full_text\":\"Haapa says hello!\"}],");
		fflush(stdout);
	}


	event_init();
	event_set(&ev, 0, EV_PERSIST, tick, NULL);
	evtimer_add(&ev, &tv);
	event_dispatch();

	return 0;
}
