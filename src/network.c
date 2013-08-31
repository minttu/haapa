#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "config.h"
#include "result.h"
#include "network.h"

Result *network_ip(char *str) {
	Result *res;
	res = init_res();

	int fd;
	struct ifreq ifr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	ifr.ifr_addr.sa_family = AF_INET;

	strncpy(ifr.ifr_name, str, IFNAMSIZ-1);

	ioctl(fd, SIOCGIFADDR, &ifr);

	close(fd);
	sprintf(res->string,
		"%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

	return res;
}

int net_ifup(char *str) {
	int fd;
	struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;

    memset(&ifr, 0, sizeof(ifr));

    strncpy(ifr.ifr_name, str, IFNAMSIZ-1);

    ioctl(fd, SIOCGIFFLAGS, &ifr);

    close(fd);

    return !!(ifr.ifr_flags & IFF_UP);
}

int net_ifdown(char *str) { return !(net_ifup(str)); }
