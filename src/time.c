#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "time.h"
#include "config.h"
#include "result.h"

Result* time_date(char* str) {
	Result* res;
	res = init_res();
	time_t timer;
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(res->string, 64, str, tm_info);

	return res;
}
