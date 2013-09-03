#include "config.h"
#include "result.h"

#ifdef INCLUDE_IWLIB

#include <stdlib.h>
#include <stdio.h>
#include <iwlib.h>

int _wireless_update(char *ifname) {
    int sock;
    struct wireless_info info = {};
    if((sock = iw_sockets_open()) < 0)
        return -1;
    iw_get_basic_config(sock, ifname, &(info.b));
    if(iw_get_range_info(sock, ifname, &(info.range)) >= 0)
        info.has_range = 1;
    if(iw_get_stats(sock, ifname, &(info.stats), &info.range, info.has_range) >= 0)
        info.has_stats = 1;
}

/* todo: general _wireless_init() */
Result *wireless_essid(char *str) {
    struct iwreq *val;
    int sock;
    Result *res;

    res = init_res();
    val = calloc(sizeof(struct iwreq), 1);
    strcat(val->ifr_name, str);
    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        free(val);
        res->error = -1;
        return res;
    }
    val->u.essid.pointer = calloc(sizeof(char) * IW_ESSID_MAX_SIZE + 1, 1);
    val->u.essid.length = IW_ESSID_MAX_SIZE;

    if(ioctl(sock, SIOCGIWESSID, val) < 0) {
        free(val->u.essid.pointer);
        free(val);
        close(sock);
        res->error = -1;
        return res;
    }

    strcat(res->string, val->u.essid.pointer);
    close(sock);
    free(val->u.essid.pointer);
    free(val);
    return res;
}

Result *wireless_signal(char *str) {
    struct iwreq *val;
    int sock;
    Result *res;

    res = init_res();
    val = calloc(sizeof(struct iwreq), 1);
    strcat(val->ifr_name, str);
    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        free(val);
        res->error = -1;
        return res;
    }
    val->u.essid.pointer = calloc(sizeof(char) * IW_ESSID_MAX_SIZE + 1, 1);
    val->u.essid.length = IW_ESSID_MAX_SIZE;

    if(ioctl(sock, SIOCGIWESSID, val) < 0) {
        free(val->u.essid.pointer);
        free(val);
        close(sock);
        res->error = -1;
        return res;
    }

    strcat(res->string, val->u.essid.pointer);
    close(sock);
    free(val->u.essid.pointer);
    free(val);
    return res;
}
#else
Result *wireless_essid() {
    Result *res = init_res();
    res->error = -1;
    return res;
}
Result *wireless_signal() {
    Result *res = init_res();
    res->error = -1;
    return res;
}
#endif
