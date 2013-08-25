#ifndef HAAPA_PROC_H
#define HAAPA_PROC_H

#include "result.h"

Result* _proc_load();
Result* (*proc_load)();

Result* _proc_memory();
Result* (*proc_memory)();

Result* _proc_cpu();
Result* (*proc_cpu)();

Result* _proc_uptime();
Result* (*proc_uptime)();

#define proc_github_stop_detecting_cpp_please
#define proc_github_stop_detecting_cpp_please2
#define proc_github_stop_detecting_cpp_please3
#define proc_github_stop_detecting_cpp_please4

#endif