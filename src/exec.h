#ifndef HAAPA_EXEC_H
#define HAAPA_EXEC_H

#include "result.h"

int _exec(char *cmd, Result *res);
Result *exec(char *cmd);

#endif
