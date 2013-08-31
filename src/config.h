#ifndef CONFIG_H
#define CONFIG_H

#define OUTPUT \
s( t("wlan0 down");, "#ff0000", network_interface_down) \
s( t("\u21CB "); string(wireless_essid); t(" "); string(network_ip); ,"#5F9F74", network_interface_up) \
s( t("\u2764 "); bar(proc_cpu); ,"#B94557", true) \
s( t("\u2263 "); bar(proc_memory); ,"#B28D4C", true) \
s( t("\u2607 "); string(battery_status); t(": "); bar(battery_capacity); ,"#9933CC", true) \
s( t("| "); string(time_date); ,"#FFFFFF", true) \

/*

static const int format = FORMAT_I3; // FORMAT_I3 or FORMAT_PLAIN
static const int interval = 1 // in seconds
static const char batterypath[] = "/sys/class/power_supply/"

static const Segment segments[] = {
	{text,		{.s = "wlan0 down"}, 						"#ff0000", true, 					{}},
	{text,  	{.s = "\u21CB"},							"#5F9F74", true, 					{}},
	{string,	{.c = wireless_essid}, 						"#5F9F74", network_interface_up, 	{.s = "wlan0"},
	{string,	{.c = network_ip, .a = {.s = "wlan0"}}, 	"#5F9F74", network_interface_up, 	{.s = "wlan0"},
	{text,		{.s = "\u2764"}, 							"#B94557", true, 					{}},
	{bar,		{.c = proc_cpu}, 							"#B94557", true, 					{}},
	{text,  	{.s = "\u2263"}, 							"#B28D4C", true, 					{}},
	{bar,		{.c = proc_memory}, 						"#B28D4C", true, 					{}},
	{text,  	{.s = "\u2607"}, 							"#9933CC", true, 					{}},
	{bar,		{.c = battery_capacity, .a = {.s = "BAT0"}},"#9933CC", true, 					{}},
	{text,		{.s = "|"}, 								"#FFFFFF", true, 					{}},
	{string,	{.c = time_date, .a = {.s = "%T"}}, 		"#FFFFFF", true, 					{}}
};
*/

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
