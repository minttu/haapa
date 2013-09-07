#ifndef HAAPA_ACPI_H
#define HAAPA_ACPI_H

#include "result.h"

Result *battery_status(char *str);

Result *battery_capacity(char *str);

int bat_exists(char *str);
int bat_islow(char *str);

Result *cpu_temp(char *str);

int if_cpu_temp(char *str);

#endif
