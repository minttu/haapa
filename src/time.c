#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "time.h"
#include "config.h"
#include "result.h"

Result* time_date() {
	Result* res;
	res = init_res();
	time_t timer;
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(res->string, 64, TIME_FORMAT, tm_info);

	return res;
}
