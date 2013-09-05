#ifndef HAAPA_BATTERY_H
#define HAAPA_BATTERY_H

#include "result.h"

Result *battery_status(char *str);

Result *battery_capacity(char *str);

int bat_exists(char *str);

#endif
