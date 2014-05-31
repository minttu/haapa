#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>

#include "config.h"
#include "result.h"
#include "network.h"

Result *network_ip(char *str) {
    Result *res;
    res = init_res();

    struct ifaddrs *ifaddr, *ifa;
    int family;
    char host[NI_MAXHOST];

    getifaddrs(&ifaddr);

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) {
            continue;
        }

        family = ifa->ifa_addr->sa_family;

        if (strcmp(ifa->ifa_name, str) != 0) {
            continue;
        }

        if (family == AF_INET) {
            getnameinfo(ifa->ifa_addr,
                        (family == AF_INET) ? sizeof(struct sockaddr_in) :
                        sizeof(struct sockaddr_in6),
                        host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            strcpy(res->string, host);
        }
    }

    freeifaddrs(ifaddr);

    return res;
}

int net_ifup(char *str) {
    struct ifaddrs *ifaddr, *ifa;
    int family;

    getifaddrs(&ifaddr);

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) {
            continue;
        }

        family = ifa->ifa_addr->sa_family;

        if (strcmp(ifa->ifa_name, str) != 0) {
            continue;
        }

        if (family == AF_INET) {
            freeifaddrs(ifaddr);
            return true;
        }
    }

    freeifaddrs(ifaddr);

    return false;
}

int net_ifdown(char *str) {
    return !(net_ifup(str));
}
