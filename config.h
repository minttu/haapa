#ifndef CONFIG_H
#define CONFIG_H

#define OUTPUT \
t("\u2665") CPU \
t("\u2263") MEM \
t("\u2607") BAT \
t("|") TIME	

/* Order of segments from ltr
 * Possible values:
 * TIME, LOAD, UPTIME, CPU, MEM, t(text)
 */

#define INTERVAL 1 					/* 1 - N */
#define INPLACE 0					/* Should it be printed ontop of itself */
#define SEGMENT_LENGTH 64
#define SEGMENT_SEPERATOR " " 		/* seperator of segments */
#define BAR_FORMAT "[%s]" 			/* %s where the bar goes */

#define TIME_FORMAT "%H:%M:%S" 		/* strftime format */
#define UPTIME_FORMAT "%T" 			/* strftime format */
#define LOAD_TIME 0 				/* 0: 5min 1: 10min 2: 15min 3: all */
#define CPU_USAGE_DISPLAY 1 		/* 0: percentage 1: bar */
#define MEM_USAGE_DISPLAY 1 		/* 0: percentage 1: bar 2: used/all MB */
#define BAT_DISPLAY 1				/* 0: percentage 1: bar */
#define BAT_LOCATION \
"/sys/class/power_supply/BAT0/"		/* where the battery is located */

#endif