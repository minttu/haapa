#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

#include "haapa.h"
#include "config.h"
#include "result.h"
#include "proc.h"
#include "time.h"
#include "battery.h"
#include "network.h"

#ifdef INCLUDE_IWLIB
#include "wireless.h"
#endif
#ifdef INCLUDE_MPD
#include "mpd.h"
#endif

static const format_type output_format = FORMAT_I3;     /* FORMAT_PLAIN or FORMAT_I3 */
static const bool output_ontop = false;                 /* is printed ontop of self */
static const int interval = 1;                          /* time in seconds between ticks */
static const char batpath[] = "/sys/class/power_supply/";
static const char segment_seperator[] = " ";

static const Segment segments[] = {
#ifdef INCLUDE_IWLIB
    {string,    text,               "\u21CB",   "#5F9F74", always,      ""},
    {string,    wireless_essid,     "wlan0",    "#5F9F74", net_ifup,    "wlan0"},
    {string,    network_ip,         "wlan0",    "#5F9F74", net_ifup,    "wlan0"},
    {string,    text,               "down",     "#FF0000", net_ifdown,  "wlan0"},
#endif
    {string,    text,               "\u2764",   "#B94557", always,      ""},
    {bar,       proc_cpu,           "",         "#B94557", always,      ""},
    {string,    text,               "\u2263",   "#B28D4C", always,      ""},
    {bar,       proc_memory,        "",         "#B28D4C", always,      ""},
    {string,    text,               "\u2607",   "#9933CC", always,      ""},
    {string,    battery_status,     "BAT0",     "#9933CC", always,      ""},
    {bar,       battery_capacity,   "BAT0",     "#9933CC", always,      ""},
    {string,    text,               "|",        "#FFFFFF", always,      ""},
    {string,    time_date,          "%T",       "#FFFFFF", always,      ""}
};

static const char mpd_hostname[] = "localhost";
static const int  mpd_port = 0;
static const int  mpd_timeout = 30000;
static const bool mpd_use_password = false;
static const char mpd_pass[] = "";

#endif
