#ifndef HAAPA_H
#define HAAPA_H

void status_time(char* str);
void status_load(char* str);
void status_uptime(char* str);
void status_cpu(char* str);
void status_mem(char* str);
void status_bat(char* str);

void status_bar(char* str, float value);
void status_text(char* str, char* in);

void tick(int fd, short event, void* arg);

#define F 		flush(buffer, result);
#define TIME 	status_time(result); F
#define LOAD 	status_load(result); F
#define UPTIME 	status_uptime(result); F
#define CPU 	status_cpu(result); F
#define MEM 	status_mem(result); F
#define BAT 	status_bat(result); F
#define t(in) 	status_text(result, in); F

#endif