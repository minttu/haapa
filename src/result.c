#include <sys/types.h>
#include "result.h"
#include <stdlib.h>

Result *init_res() {
	Result *res = malloc(sizeof(Result));
	res->string[0] = 0;
	res->value = 0.0f;
	res->max = 0.0f;
	res->time_value = 0;
	res->status = -1;
	res->error = 0;
	return res;
}
