#ifndef FORMAT_H
#define FORMAT_H

typedef struct {
	char *init;
	char *start;
	char *end;
	void (*segment)(char *buffer, char *str, char *color);
} Format;

Format *format_init();

Format *format_plain();
Format *format_i3();
Format *format_i3_manual();
Format *format_dzen();
Format *format_xmobar();
Format *format_x256();

#define i3_manual_s "!i3_manual_start"
#define i3_manual_e "!i3_manual_end"

int is_format(char *str);

#endif