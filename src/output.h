#ifndef OUTPUT_H
#define OUTPUT_H

#ifdef INCLUDE_XLIB
void output_x(char *str);
#endif

void output_plain(char *str);
void output_ontop(char *str);

#endif