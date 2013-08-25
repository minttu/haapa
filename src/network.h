#ifndef HAAPA_NETWORK_H
#define HAAPA_NETWORK_H

#include "result.h"

Result* _network_ip();
Result* (*network_ip)();

#define network_github_stop_detecting_cpp_please

#endif