#ifndef CONFIG_H
#define CONFIG_H

#include "modules.h"

static const format_type output_format = FORMAT_PLAIN;  /* FORMAT_PLAIN or FORMAT_I3 */
static const bool output_ontop = false;					/* is printed ontop of self */
static const int interval = 1;							/* time in seconds between ticks */
static const char *const batpath = "/sys/class/power_supply/";
static const char *const segment_seperator = " ";

static const char *const mpd_hostname = NULL;
static const char *const mpd_pass = NULL;
static const int  mpd_port = 0;
static const int  mpd_timeout = 30000;

static const Segment segments[] = {
	{string,	mpd_uri,			"",			"#FFFFFF", mpd_playing, ""},
	{string,	mpd_artist,			"",			"#FFFFFF", mpd_playing, ""},
	{string,	text, 				"\u21CB",	"#5F9F74", always, 		""},
	{string,	wireless_essid,		"wlan0",	"#5F9F74", net_ifup,	"wlan0"},
	{string,	network_ip,			"wlan0",	"#5F9F74", net_ifup,	"wlan0"},
	{string,	text,				"down",		"#FF0000", net_ifdown,	"wlan0"},
	{string,	text,				"\u2764", 	"#B94557", always,		""},
	{bar,		proc_cpu,			"",			"#B94557", always,		""},
	{string,	text,				"\u2263",	"#B28D4C", always,		""},
	{bar,		proc_memory,		"",			"#B28D4C", always,		""},
	{string,	text,				"\u2607",	"#9933CC", always,		""},
	{string,	battery_status,		"BAT0",		"#9933CC", always,		""},
	{bar,		battery_capacity,	"BAT0",		"#9933CC", always,		""},
	{string,	text,				"|",		"#FFFFFF", always,		""},
	{string,	time_date,			"%T",		"#FFFFFF", always,		""}
};

#endif
