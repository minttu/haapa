#ifndef HAAPA_NETWORK_H
#define HAAPA_NETWORK_H

#include "result.h"

Result* _network_ip();
Result* (*network_ip)();
Result *network_essid();

int _network_interface_up();
int (*network_interface_up)();

int _network_interface_down();
int (*network_interface_down)();

#define network_github_stop_detecting_cpp_please
#define network_github_stop_detecting_cpp_please2
#define network_github_stop_detecting_cpp_please3

#endif
