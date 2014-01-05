#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"
#include "config.h"

#include "x256.h"

char* format_name;

Format *format_init(char *str) {
    format_name = str;
    Format *f = malloc(sizeof(Format));
    f->init = "";
    f->start = "";
    f->end = "";
    f->segment = NULL;
    return f;
}

void format_plain_segment(char *buffer, char *str, char *color) {
    strcat(buffer, str);
    strcat(buffer, segment_seperator);
}

Format *format_plain() {
    Format *f;
    f = format_init("plain");
    f->init = "Haapa says hello!\n";
    f->start = "";
    f->end = "";
    f->segment = format_plain_segment;
    return f;
}

void format_i3_segment(char *buffer, char *str, char *color) {
    char colorbuffer[64];

    strcat(buffer, ",{\"full_text\":\"");
    strcat(buffer, str);
    colorbuffer[0] = 0;
    sprintf(colorbuffer, "\",\"color\":\"%s\"}\n", color);
    strcat(buffer, colorbuffer);
}

Format *format_i3() {
    Format *f;
    f = format_init("i3");
    f->init = "{\"version\":1}\n[[{\"full_text\":\"Haapa says hello!\"}],";
    f->start = "[{\"full_text\":\"\"}\n";
    f->end = "],";
    f->segment = format_i3_segment;
    return f;
}

void format_i3_manual_segment(char *buffer, char *str, char *color) {
    if(strcmp(i3_manual_s, str) == 0) {
        strcat(buffer, ",{\"full_text\":\"");
    }else if(strcmp(i3_manual_e, str) == 0) {
        char colorbuffer[64];
        colorbuffer[0] = 0;
        sprintf(colorbuffer, "\",\"color\":\"%s\"}\n", color);
        strcat(buffer, colorbuffer);
    }else{
        strcat(buffer, str);
        strcat(buffer, segment_seperator);
    }
}

Format *format_i3_manual() {
    Format *f;
    f = format_init("i3_manual");
    f->init = "{\"version\":1}\n[[{\"full_text\":\"Haapa says hello!\"}],";
    f->start = "[{\"full_text\":\"\"}\n";
    f->end = "],";
    f->segment = format_i3_manual_segment;
    return f;
}

void format_dzen_segment(char *buffer, char *str, char *color) {
    char colorbuffer[64];
    sprintf(colorbuffer, "^fg(\\%s)", color);
    strcat(buffer, colorbuffer);
    strcat(buffer, str);
    strcat(buffer, segment_seperator);
}

Format *format_dzen() {
    Format *f;
    f = format_init("dzen");
    f->init = "Haapa says hello!\n";
    f->start = "";
    f->end = "";
    f->segment = format_dzen_segment;
    return f;
}

void format_xmobar_segment(char *buffer, char *str, char *color) {
    char colorbuffer[64];
    sprintf(colorbuffer, "<fc=%s>", color);
    strcat(buffer, colorbuffer);
    strcat(buffer, str);
    strcat(buffer, "</fc>");
    strcat(buffer, segment_seperator);
}

Format *format_xmobar() {
    Format *f;
    f = format_init("xmobar");
    f->init = "Haapa says hello!\n";
    f->start = "";
    f->end = "";
    f->segment = format_xmobar_segment;
    return f;
}

void format_x256_segment(char *buffer, char *str, char *color) {
    char colorbuffer[64];
    sprintf(colorbuffer, "\x1b[38;5;%im", get_x256(color));
    strcat(buffer, colorbuffer);
    strcat(buffer, str);
    strcat(buffer, "\x1b[0m");
    strcat(buffer, segment_seperator);
}

Format *format_x256() {
    Format *f;
    f = format_init("x256");
    f->init = "Haapa says hello!\n";
    f->start = "";
    f->end = "";
    f->segment = format_x256_segment;
    return f;
}

int is_format(char *str) {
    if(strcmp(format_name, str)==0)
        return 1;
    return 0;
}