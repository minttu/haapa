#ifndef HAAPA_PROC_H
#define HAAPA_PROC_H

#include "result.h"

Result *proc_load(char *str);
Result *proc_memory();
Result *proc_cpu();
Result *proc_uptime();
Result *proc_cpu_mhz();

#endif
