#ifndef CONFIG_H
#define CONFIG_H

/*
#define OUTPUT \
t("\u21CB") IP \
t("\u2764") CPU \
t("\u2263") MEM \
t("\u2607") BAT \
t("|") TIME	
*/

#define OUTPUT \
I3S \
I3B t("\u21CB") IP I3C("#5F9F74") \
I3B t("\u2764") CPU I3C("#B94557") \
I3B t("\u2263") MEM I3C("#B28D4C") \
I3B t("\u2607") BAT I3C("#9933CC") \
I3B t("|") TIME I3C("#FFFFFF") \
I3E

/* Order of segments from ltr
 * Possible values:
 * TIME, LOAD, UPTIME, CPU, MEM, t(text)
 */

#define FORMAT 0					/* 0: \n 1: ontop */
#define I3_ENABLED 1				/* is I3 format enabled */
#define INTERVAL 1 					/* 1 - N */
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
#define IP_INTERFACE "wlan0"

#endif