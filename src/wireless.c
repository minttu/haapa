#include <stdlib.h>
#include <stdio.h>
#include <iwlib.h>

#include "config.h"
#include "result.h"

Result *network_essid() {
    Result *res;
    struct iwreq *val;
    int sock;

    res = init_res();
    val = calloc(sizeof(struct iwreq), 1);
    val->u.essid.pointer = malloc(sizeof(char) * IW_ESSID_MAX_SIZE + 1);
    val->u.essid.length = IW_ESSID_MAX_SIZE;
    ((char *)(val->u.essid.pointer))[0] = 0;
    strcat(val->ifr_name, NETWORK_INTERFACE);
    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        res->error = -1;
        free(val->u.essid.pointer);
        free(val);
        return res;
    }
    if(ioctl(sock, SIOCGIWESSID, val)<0) {
        res->error = -1;
        free(val);
        return res;
    }

    strcat(res->string, val->u.essid.pointer);
    free(val->u.essid.pointer);
    free(val);
    return res;
}

