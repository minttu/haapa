#ifndef CONFIG_H
#define CONFIG_H

#define OUTPUT \
s( t("\u266A "); string(mpd_uri); t(" "); timeconv(mpd_sels); t("/"); timeconv(mpd_slen); ,"#FFFFFF", true) \
s( t("wlan0 down");, "#ff0000", network_interface_down) \
s( t("\u21CB Essid:"); string(wireless_essid); t(" "); ,"#5F9F74", network_interface_up) \
s( t("\u2764 "); bar(proc_cpu); ,"#B94557", true) \
s( t("\u2263 "); bar(proc_memory); ,"#B28D4C", true) \
s( t("\u2607 "); string(battery_status); t(": "); bar(battery_capacity); ,"#9933CC", true) \
s( t("| "); string(time_date); ,"#FFFFFF", true) \


#define FORMAT 0					/* 0: \n 1: ontop */
#define I3_ENABLED 0				/* is I3 format enabled */
#define INTERVAL 1 					/* 1 - N */
#define BATTERY_LOCATION "/sys/class/power_supply/BAT0/"
#define NETWORK_INTERFACE "wlan0"
#define PROC_LOAD_TIME 0
#define TIME_FORMAT "%H:%M:%S"

#define MPD_HOSTNAME NULL
#define MPD_PORT 0
#define MPD_TIMEOUT 30000
#define MPD_PASS NULL

#endif
