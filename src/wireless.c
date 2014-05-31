#include "config.h"

#ifdef INCLUDE_IWLIB

#include "result.h"
#include "wireless.h"
#include <stdlib.h>
#include <stdio.h>
#include <iwlib.h>

wireless_response *wir_response = NULL;
static int wireless_updated = 0;

void _wireless_reset() {
    wireless_updated = 0;
}

int _wireless_update(char *ifname) {
    int sock;
    struct wireless_info info = {};
    struct iwreq req;

    if (!wir_response) {
        wir_response = malloc(sizeof(wireless_response));
        wir_response->essid = malloc(IW_ESSID_MAX_SIZE + 1);
        wir_response->int_max[0] = 1;
        wir_response->int_max[1] = 1;
        wir_response->int_max[2] = 1;
        wir_response->int_max[3] = 100;
    }

    if ((sock = iw_sockets_open()) < 0) {
        return -1;
    }

    iw_get_basic_config(sock, ifname, &(info.b));

    if (iw_get_ext(sock, ifname, SIOCGIWAP, &req)) { /* AP addr */
        info.has_ap_addr = 1;
        memcpy(&(info.ap_addr), &(req.u.ap_addr), sizeof(sockaddr));
    }

    if (iw_get_ext(sock, ifname, SIOCGIWRATE, &req) >= 0) { /* bit rate */
        info.has_bitrate = 1;
        memcpy(&(info.bitrate), &(req.u.bitrate), sizeof(iwparam));
    }

    if (iw_get_range_info(sock, ifname, &(info.range)) >= 0) { /* range */
        info.has_range = 1;
    }

    if (iw_get_stats(sock, ifname, &(info.stats),
                     &info.range, info.has_range) >= 0) {
        info.has_stats = 1;
    }

    if (info.b.has_freq) {
        if (info.has_range && info.b.freq < 1000) {
            wir_response->channel = iw_channel_to_freq(
                                        (int)info.b.freq, &wir_response->freq, &info.range);

            if (wir_response->channel < 0) {
                wir_response->channel = 0;
            }

            wir_response->freq = 0;
        } else {
            wir_response->channel = -1;
            wir_response->freq = info.b.freq;
        }
    }

    wir_response->essid[0] = 0;
    strncat(wir_response->essid, info.b.essid, IW_ESSID_MAX_SIZE - 1);

    if (info.has_stats) {
        wir_response->quality = info.stats.qual.qual;
        wir_response->q_max = info.range.max_qual.qual;
    }

    iw_sockets_close(sock);
    wireless_updated = 0;
    return 0;
}

/* todo: general _wireless_init() */
#define M() \
    Result *res; \
    if(!wireless_updated) \
        _wireless_update(ifname); \
    res = init_res()

Result *wireless_essid(char *ifname) {
    M();
    strncat(res->string, wir_response->essid, sizeof(res->string) - 1);
    return res;
}

Result *wireless_ap_addr(char *ifname) {
    M();
    strncat(res->string, wir_response->ap_addr, sizeof(res->string) - 1);
    return res;
}

Result *wireless_freq(char *ifname) {
    M();
    res->max = wir_response->freq_max;
    res->value = wir_response->freq;
    snprintf(res->string, sizeof(res->string) - 1, "%f", wir_response->freq);
    return res;
}

Result *wireless_chan(char *ifname) {
    M();
    res->max = wir_response->chan_max;
    res->value = wir_response->channel;
    snprintf(res->string, sizeof(res->string) - 1, "%d", wir_response->channel);
    return res;
}

Result *wireless_bitrate(char *ifname) {
    M();
    res->max = wir_response->bit_max;
    res->value = wir_response->bitrate;
    snprintf(res->string, sizeof(res->string) - 1, "%d", wir_response->bitrate);
    return res;
}

Result *wireless_quality(char *ifname) {
    M();

    if (wir_response->q_max == 0) {
        wir_response->q_max = 1;
    }

    res->max = wir_response->q_max;
    res->value = wir_response->quality;
    snprintf(res->string, sizeof(res->string) - 1, "%d",
             (wir_response->quality * 100) / wir_response->q_max);
    return res;
}

#undef M

#endif
