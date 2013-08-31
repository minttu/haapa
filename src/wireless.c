#include <stdlib.h>
#include <stdio.h>
#include <iwlib.h>

#include "config.h"
#include "result.h"
#include "iwlib.h"

/* todo: general _wireless_init() */
Result *wireless_essid(char* str) {
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
    val->u.essid.pointer = malloc(sizeof(char) * IW_ESSID_MAX_SIZE + 1);
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

