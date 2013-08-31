#ifndef HAAPA_H
#define HAAPA_H
#include "result.h"

void start_segment();
void end_segment(char *color);
void string(Result *(*function)(char *str), char *str);
void bar(Result *(*function)(char *str), char *str);
void timeconv(Result *(*function)(char *str), char *str);
Result *text(char *str);
int always(char *str);
int never(char *str);

void tick(int fd, short event, void *arg);

typedef enum {
	FORMAT_PLAIN,
	FORMAT_I3
} format_type;

typedef struct {
	void (*output_function)();
	Result *(*function)(char *str);
	char *function_argument;
	char *color;
	int (*condition_function)(char *str);
	char *condition_argument;
} Segment;

#endif
