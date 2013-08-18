#ifndef HAAPA_H
#define HAAPA_H

void status_time(char* str);
void status_load(char* str);
void status_uptime(char* str);
void status_cpu(char* str);
void status_mem(char* str);

void status_bar(char* str, float value);
void status_text(char* str, char* in);

void tick(int fd, short event, void* arg);

#define TIME status_time(result); flush(buffer, result);
#define LOAD status_load(result); flush(buffer, result);
#define UPTIME status_uptime(result); flush(buffer, result);
#define CPU status_cpu(result); flush(buffer, result);
#define MEM status_mem(result); flush(buffer, result);
#define t(in) status_text(result, in); flush(buffer, result);

#endif