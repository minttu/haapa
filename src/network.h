#ifndef HAAPA_NETWORK_H
#define HAAPA_NETWORK_H

#include "result.h"

Result *network_ip(char *str);

int net_ifup(char *str);

int net_ifdown(char *str);

#endif
