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

#include "modules.h"
#include "output.h"
#include "util.h"

static const char *bar_unicode[2][8] = {
    {
        "\u2581", "\u2582", "\u2583", "\u2584",
        "\u2585", "\u2586", "\u2587", "\u2588"
    },
    {
        "\u258F", "\u258E", "\u258D", "\u258C",
        "\u258B", "\u258A", "\u2589", "\u2588"
    }
};

char buffer[2048];
char *output;
int ticktock;

static String *previous_strings[sizeof(segments)];

Format *f;

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

void string(Result * (*function)(char *str), char *str) {
    Result *res = function(str);

    if (res->hidden) {
        goto done;
    }

    if (res->error) {
        strcat(buffer, "error");
        goto done;
    }

    if (res->string[0] == 0) {
        snprintf(res->string, sizeof(res->string), "%f", res->value);
        strcat(buffer, res->string);
    } else {
        strcat(buffer, res->string);
    }

done:
    free(res);
}

Result *text(char *str) {
    Result *res = init_res();
    strcpy(res->string, str);
    return res;
}

void bar(Result * (*function)(char *str), char *str) {
    Result *res = function(str);

    char bar[bar_format_length * 3 + 2];
    char buffbar[bar_format_length * 3 + 8];
    int i;
    float value;
    float tmp_val;

    if (res->hidden) {
        goto done;
    }

    if (res->error) {
        strcat(buffer, "error");
        goto done;
    }

    if (bar_format_unicode == 0) {
        value = (res->value / res->max) * bar_format_length;
    } else {
        value = (res->value / res->max) * 8 * bar_format_length;
    }

    tmp_val = round(value);

    bar[0] = 0;

    for (i = 0; i < bar_format_length; i++) {
        if (bar_format_unicode == 0) {
            if (i < tmp_val) {
                strcat(bar, "#");
            } else {
                strcat(bar, "_");
            }
        } else {
            if (i * 8 < tmp_val) {
                if (tmp_val - i * 8 > 0 && tmp_val - i * 8 < 9) {
                    strcat(bar, bar_unicode[bar_format_unicode - 1][((int)tmp_val - i * 8) - 1]);
                } else {
                    strcat(bar, bar_unicode[bar_format_unicode - 1][7]);
                }
            } else {
                strcat(bar, " ");
            }
        }
    }

    sprintf(buffbar, bar_format, bar);
    strcat(buffer, buffbar);

done:
    free(res);
}

void percent(Result * (*function)(char *str), char *str) {
    Result *res = function(str);

    if (res->hidden) {
        goto done;
    }

    char per[5];
    per[0] = 0;

    if (res->error) {
        strcat(buffer, "error");
        goto done;
    }

    sprintf(per, "%3i%%", (int)round((res->value / res->max) * 100));
    strcat(buffer, per);

done:
    free(res);
}

void timeconv(Result * (*function)(char *str), char *str) {
    Result *res = function(str);

    char buf[128];
    buf[0] = 0;
    int h, m, s;

    if (res->hidden) {
        goto done;
    }

    if (res->error) {
        strcat(buffer, "error");
        goto done;
    }

    h = ((int)res->value / (60 * 60)) % 60;
    m = ((int)res->value / 60) % 60;
    s = ((int)res->value) % 60;

    if (h) {
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d", h, m, s);
    } else {
        snprintf(buf, sizeof(buf), "%02d:%02d", m, s);
    }

    strcat(buffer, buf);

done:
    free(res);
}

/* chunk down bytes to precision of 2 decimals and KB, MB etc */
void sizeconv(Result * (*function)(char *str), char *str) {
    Result *res = function(str);

    char buf[128];
    buf[0] = 0;
    unsigned long g, m, k, b;

    if (res->hidden) {
        goto done;
    }

    if (res->error) {
        strcat(buffer, "error");
        goto done;
    }

    b = ((unsigned long)res->value) % 1000;
    k = ((unsigned long)res->value / (1000)) % 1000;
    m = ((unsigned long)res->value / (1000 * 1000)) % 1000;
    g = ((unsigned long)res->value / (1000 * 1000 * 1000)) % 1000;

    if (g) {
        snprintf(buf, sizeof(buf), "%lu.%lu GB", g, m / 100);
        strcat(buffer, buf);
    } else if (m) {
        snprintf(buf, sizeof(buf), "%lu.%lu MB", m, k / 100);
        strcat(buffer, buf);
    } else if (k) {
        snprintf(buf, sizeof(buf), "%lu.%lu kB", k, b / 100);
        strcat(buffer, buf);
    } else {
        snprintf(buf, sizeof(buf), "%lu B", b);
        strcat(buffer, buf);
    }

done:
    free(res);
}

/* same but GiB etc */
void sizeconvi(Result * (*function)(char *str), char *str) {
    Result *res = function(str);

    char buf[128];
    buf[0] = 0;
    unsigned long g, m, k, b;

    if (res->hidden) {
        goto done;
    }

    if (res->error) {
        strcat(buffer, "error");
        goto done;
    }

    b = ((unsigned long)res->value) % 1024;
    k = ((unsigned long)res->value) / 1024 % 1024;
    m = ((unsigned long)res->value) / 1024 / 1024 % 1024;
    g = ((unsigned long)res->value) / 1024 / 1024 / 1024 % 1024;

    if (g) {
        snprintf(buf, sizeof(buf), "%lu.%lu GiB", g, m / 100);
        strcat(buffer, buf);
    } else if (m) {
        snprintf(buf, sizeof(buf), "%lu.%lu MiB", m, k / 100);
        strcat(buffer, buf);
    } else if (k) {
        snprintf(buf, sizeof(buf), "%lu.%lu kiB", k, b / 100);
        strcat(buffer, buf);
    } else {
        snprintf(buf, sizeof(buf), "%lu B", b);
        strcat(buffer, buf);
    }

done:
    free(res);
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
    _mpd_reset();
#endif
#ifdef INCLUDE_ALSA
    _alsa_reset();
#endif
#ifdef INCLUDE_IWLIB
    _wireless_reset();
#endif
    _fs_reset();
    _proc_speed_reset();
    output[0] = 0;

    if (f->start != NULL) {
        strcat(output, f->start);
    }

    for (i = 0; i < sizeof(segments) / sizeof(segments[0]); i++) {
        Segment segment = segments[i];

        if (segment.condition_function(segment.condition_argument) == 1) {
            String *previous = previous_strings[i];
            buffer[0] = 0;
            segment.output_function(segment.function,
                                    segment.function_argument);

            string_update(previous, buffer);

            if (buffer[0] == 0) {
                continue;
            }

            char *cur = string_get(previous);
            buffer[0] = 0;
            strcat(buffer, cur);

            if (formatter == format_i3) {
                char *tmp = jsonescape(buffer);
                buffer[0] = 0;
                strcat(buffer, tmp);

                if (tmp) {
                    free(tmp);
                }
            }

            if (strlen(segment.color) > 7) {
                char *colbuf = NULL;
                char ogbuf[16];
                strcpy(ogbuf, segment.color);
                colbuf = strtok(ogbuf, ",");

                if (!ticktock) {
                    f->segment(output, buffer, colbuf);
                } else {
                    colbuf = strtok(NULL, ",");
                    f->segment(output, buffer, colbuf);
                }
            } else {
                f->segment(output, buffer, segment.color);
            }
        }
    }

    if (f->end != NULL) {
        strcat(output, f->end);
    }

    outputter(output);

    if (arguments.once) {
        exit(0);
    }

    ticktock = !ticktock;
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
    printf("Copyright (c) 2013, contributors of the haapa project\n");
    printf("License MIT, see LICENSE for more detail\n");
    exit(0);
}

int main(int argc, char *const argv[]) {
    struct event ev;
    struct timeval tv;
    int opt;
    int longIndex = 0;
    int i;

    arguments.once = 0;

    tv.tv_sec = interval;
    tv.tv_usec = 0;

    opt = getopt_long( argc, argv, optString, longOpts, &longIndex );

    while ( opt != -1 ) {
        switch ( opt ) {
            case 'o':
                arguments.once++;
                tv.tv_sec = 0;
                break;

            case 'v':
                display_version();
                break;

            case 'h':
            case '?':
                display_usage();
                break;

            default:
                break;
        }

        opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    }

    for (i = 0; i < sizeof(segments) / sizeof(segments[0]); i++) {
        previous_strings[i] = calloc(1, sizeof(String));
        previous_strings[i]->dir = 1;
    }

    f = formatter();
    output = malloc(sizeof(char) * 2048);

    if (f->init != NULL) {
        outputter(f->init);
    }

#ifdef INCLUDE_MPD
    _mpd_update();
#endif
#ifdef INCLUDE_ALSA
    _alsa_update();
#endif

    event_init();
    event_set(&ev, 0, EV_PERSIST, tick, NULL);
    evtimer_add(&ev, &tv);
    event_dispatch();

    return 0;
}

