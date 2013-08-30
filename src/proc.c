#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "proc.h"
#include "config.h"
#include "result.h"

Result* proc_load() {
	FILE* f;
	Result* res;
	res = init_res();
	float loads[3];
	int val;

	f = fopen("/proc/loadavg", "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%f %f %f", &loads[0], &loads[1], &loads[2]);
	fclose(f);
	if(val == EOF) {
		res->error=1;
		return res;
	}

#if PROC_LOAD_TIME != 3
	sprintf(res->string, "%.2f", loads[PROC_LOAD_TIME]);
#else
	sprintf(res->string, "%.2f %.2f %.2f", loads[0], loads[1], loads[2]);
#endif
	return res;
}

Result* proc_memory() {
	FILE* f;
	Result* res;
	res = init_res();
	char u[9][16];
	int mem_total, mem_free, mem_buffers, mem_cached, mem_used, val;

	f = fopen("/proc/meminfo", "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%s %i %s %s %i %s %s %i %s %s %i %s", 
		u[0], &mem_total, u[1],
		u[2], &mem_free, u[3],
		u[4], &mem_buffers, u[5],
		u[6], &mem_cached, u[7]);
	fclose(f);

	if(val == EOF) {
		res->error=1;
		return res;
	}

	mem_used = mem_total - mem_free - mem_buffers - mem_cached;

	sprintf(res->string, "%i/%i MB", mem_used/1024, mem_total/1024);
	res->value=mem_used;
	res->max=mem_total;
	return res;
}


float cpu_prev_total = 0;
float cpu_prev_idle = 0;

Result* proc_cpu() {
	FILE* f;
	Result* res;
	res = init_res();
	float total = 0;
	float idle = 0;
	int i;
	int val;
	float usage;
	float diff_idle;
	float diff_total;

	char ident[5];

	int a[7];

	f = fopen("/proc/stat", "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%s %i %i %i %i %i %i %i", 
		ident, &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6]);
	fclose(f);

	if(val == EOF) {
		res->error=1;
		return res;
	}

	idle = a[3];

	for(i = 0; i < 7; i++) {
		total += a[i];
	}

	if(cpu_prev_total > 0) {
		diff_idle = idle - cpu_prev_idle;
		diff_total = total - cpu_prev_total;
		usage = 100 * (diff_total - diff_idle) / diff_total;
		res->value = usage;
		res->max = 100;
		sprintf(res->string, "%.0f%%", usage);
	}else{
		strcpy(res->string, "");
		res->value=0;
		res->max=100;
	}

	cpu_prev_total = total;
	cpu_prev_idle = idle;

	return res;
}

Result* proc_uptime() {
	FILE* f;
	Result* res;
	res = init_res();
	float uptime = 0;
	int upint = 0;
	int days = 0;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	int val;

	f = fopen("/proc/uptime", "r");

	if(f == NULL) {
		res->error=1;
		return res;
	}

	val = fscanf(f, "%f", &uptime);
	fclose(f);

	if(val == EOF) {
		res->error=1;
		return res;
	}


	upint = (int) (uptime);

	days = upint/86400;
	hours = upint/3600 - days*24;
	minutes = upint/60 - hours*60 - days*1440;
	seconds = (upint)%60;

	sprintf(res->string, "%i days, %02i:%02i:%02i", days, hours, minutes, seconds);

	return res;
}
