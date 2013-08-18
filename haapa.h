#ifndef HAAPA_H
#define HAAPA_H

void status_time(char* str);
void status_load(char* str);
void status_uptime(char* str);
void status_cpu(char* str);
void status_mem(char* str);
void status_bat(char* str);
void status_ip(char* str);

void status_bar(char* str, float value);
void status_text(char* str, char* in);

void status_i3_start(char* str);
void status_i3_block(char* str);
void status_i3_color(char* str, char* color);
void status_i3_end(char* str);

void tick(int fd, short event, void* arg);

#define F 		flush(buffer, result);
#define F2		flush2(buffer, result);
#define F3		flush3(buffer, result);
#define TIME 	status_time(result); F
#define LOAD 	status_load(result); F
#define UPTIME 	status_uptime(result); F
#define CPU 	status_cpu(result); F
#define MEM 	status_mem(result); F
#define BAT 	status_bat(result); F
#define IP 		status_ip(result); F
#define t(in) 	status_text(result, in); F3

#define I3S		status_i3_start(result); F2
#define I3B		status_i3_block(result); F2
#define I3C(c)	status_i3_color(result, c); F2
#define I3E		status_i3_end(result); F2

#endif