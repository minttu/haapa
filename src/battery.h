#ifndef HAAPA_BATTERY_H
#define HAAPA_BATTERY_H

#include "result.h"

Result* _battery_status();
Result* (*battery_status)();

Result* _battery_capacity();
Result* (*battery_capacity)();

#define battery_github_stop_detecting_cpp_please
#define battery_github_stop_detecting_cpp_please2

#endif