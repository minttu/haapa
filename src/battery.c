#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "battery.h"
#include "config.h"
#include "result.h"

Result *battery_status(char *str) {
	Result *res;
	res = init_res();
	FILE *f;
	char file_location[128];
	int val;

	file_location[0] = 0;
	strcat(file_location, batpath);
	strcat(file_location, str);
	strcat(file_location, "/");
	strcat(file_location, "status");

	f = fopen(file_location, "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%s", res->string);
	fclose(f);

	if(val == EOF) {
		res->error=1;
		return res;
	}

	return res;
}

Result *battery_capacity(char *str) {
	Result *res;
	res = init_res();
	FILE *f;
	int capacity = 0;
	char file_location[128];
	int val;
	file_location[0] = 0;
	strcat(file_location, batpath);
	strcat(file_location, str);
	strcat(file_location, "/");
	strcat(file_location, "capacity");

	f = fopen(file_location, "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%i", &capacity);
	fclose(f);


	if(val == EOF) {
		res->error=1;
		return res;
	}

	res->max=100;
	res->value=(int)capacity;

	sprintf(res->string, "%i%%", capacity);

	return res;
}
