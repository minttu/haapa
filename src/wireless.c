#include "config.h"

#ifdef INCLUDE_IWLIB

#include "result.h"
#include "wireless.h"
#include <stdlib.h>
#include <stdio.h>
#include <iwlib.h>

wireless_response *response = NULL;
static int wireless_updated = 0;

void _wireless_reset() {
    wireless_updated = 0;
}

int _wireless_update(char *ifname) {
    int sock;
    struct wireless_info info = {};
    struct iwreq req;
    if(!response) {
        response = calloc(sizeof(wireless_response), 1);
        response->essid = malloc(IW_ESSID_MAX_SIZE + 1);
        response->int_max[0] = 1;
        response->int_max[1] = 1;
        response->int_max[2] = 1;
        response->int_max[3] = 100;
    }
    if((sock = iw_sockets_open()) < 0)
        return -1;
    iw_get_basic_config(sock, ifname, &(info.b));
    if(iw_get_ext(sock, ifname, SIOCGIWAP, &req)) { /* AP addr */
        info.has_ap_addr = 1;
        memcpy(&(info.ap_addr), &(req.u.ap_addr), sizeof(sockaddr));
    }
    if(iw_get_ext(sock, ifname, SIOCGIWRATE, &req) >= 0) /* bit rate */
    {
      info.has_bitrate = 1;
      memcpy(&(info.bitrate), &(req.u.bitrate), sizeof(iwparam));
    }

    if(iw_get_range_info(sock, ifname, &(info.range)) >= 0) /* range */
        info.has_range = 1;
    if(iw_get_stats(sock, ifname, &(info.stats),
                          &info.range, info.has_range) >= 0)
        info.has_stats = 1;

    if(info.b.has_freq) {
        if(info.has_range && info.b.freq < 1000) {
            response->channel = iw_channel_to_freq(
                            (int)info.b.freq, &response->freq, &info.range);
            if(response->channel<0)
                response->channel = 0;
                response->freq = 0;
        }
        else {
            response->channel = -1;
            response->freq = info.b.freq;
        }
    }
    strncpy(response->essid, info.b.essid, IW_ESSID_MAX_SIZE - 1);
    if(info.has_stats)
        response->quality = info.stats.qual.qual;
    wireless_updated = 0;
    return 0;
}

/* todo: general _wireless_init() */
Result *wireless_essid(char *ifname) {
    Result *res;
    if(!wireless_updated)
        _wireless_update(ifname);
    res = init_res();
    strncat(res->string, response->essid, sizeof(res->string) - 1);
    return res;
}

Result *wireless_signal(char *ifname) {
    Result *res;
    if(!wireless_updated)
        _wireless_update(ifname);
    res = init_res();
    res->max = response->q_max;
    res->value = response->quality;
    return res;
}
#endif
