#ifndef HAAPA_WIRELESS_H
#define HAAPA_WIRELESS_H

#include "result.h"

typedef struct wireless_response {
    char *essid;
    char *ap_addr;
    double freq;
    int channel;
    int bitrate;
    int quality;
    union {
        struct {
            int freq_max;
            int chan_max;
            int bit_max;
            int q_max;
        };
        int int_max[4];
    };
} wireless_response;

void _wireless_reset();
int _wireless_update();
Result *wireless_essid(char *ifname);
Result *wireless_ap_addr(char *ifname);
Result *wireless_freq(char *ifname);
Result *wireless_chan(char *ifname);
Result *wireless_bitrate(char *ifname);
Result *wireless_quality(char *ifname);

#endif
