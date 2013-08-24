#ifndef HAAPA_H
#define HAAPA_H
#include "result.h"

void start_segment();
void end_segment(char* color);
void string(Result* (*function)());
void bar(Result *(*function)());
void t(char* str);

int always_true();
int (*true)();

int always_false();
int (*false)();

void tick(int fd, short event, void* arg);

#define s(commands, color, condition) \
if(condition()){ \
	start_segment(); commands; end_segment(color); \
} 

#endif