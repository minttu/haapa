#ifndef CONFIG_H
#define CONFIG_H

#include "modules.h"
#include "format.h"
#include "output.h"

static Format *(* const formatter)() = format_plain;
static void (* const outputter)(char *str) = output_plain;
static const int interval = 1;                          /* time in seconds between ticks */
static const char *const batpath = "/sys/class/power_supply/";
static const char *const segment_seperator = " ";

static const int  bar_format_unicode = 2; /* 0: no unicode, 1: vertical, 2: horizontal */
static const char *const bar_format = "\u2502%s\u2502";
static const int  bar_format_length = 10;

static const char *const mpd_hostname = NULL;
static const char *const mpd_pass = NULL;
static const int  mpd_port = 0;
static const int  mpd_timeout = 30000;

static const char *const alsa_channel = "Master";

static const Segment segments[] = {
#ifdef INCLUDE_MPD
    {string,    text,               "\u266B",   "#859900", mpd_exists, ""},
    {string,    mpd_smart,          " - ",      "#859900", mpd_exists, ""},
    {timeconv,  mpd_sels,           "",         "#859900", mpd_exists, ""},
    {string,    text,               "/",        "#859900", mpd_exists, ""},
    {timeconv,  mpd_slen,           "",         "#859900", mpd_exists, ""},
#endif
#ifdef INCLUDE_ALSA
    {string,    text,               "\u266B",   "#859900", always,      ""},
    {bar,       alsa_volume,        "",         "#859900", alsa_nmuted, ""},
    {string,    text,               "muted",    "#859900", alsa_muted,  ""},
#endif
     {string,    text,               "\u21CB",   "#DC322F", always,      ""},
#ifdef INCLUDE_IWLIB
    {string,    wireless_essid,     "wlan0",    "#DC322F", net_ifup,    "wlan0"},
    {percent,   wireless_quality,   "wlan0",    "#DC322F", net_ifup,    "wlan0"},
    {string,    network_ip,         "wlan0",    "#DC322F", net_ifup,    "wlan0"},
#endif
    {string,    network_ip,         "eth0",     "#DC322F", net_ifup,    "eth0"},
    {string,    text,               "\u2764",   "#CB4B16", always,      ""},
    {string,    cpu_temp,           "",         "#CB4B16", if_cpu_temp, ""},
    {bar,       proc_cpu,           "",         "#CB4B16", always,      ""},
    {string,    text,               "\u2263",   "#CB4B16", always,      ""},
    {bar,       proc_memory,        "",         "#CB4B16", always,      ""},
    {string,    text,               "\u2607",   "#2AA198", bat_exists,  "BAT0"},
    {string,    battery_status,     "BAT0",     "#2AA198", bat_exists,  "BAT0"},
    {bar,       battery_capacity,   "BAT0",     "#2AA198", bat_exists,  "BAT0"},
    {string,    text,               "BAT0 Low", "#DC322F,#FFFFFF", bat_islow, "BAT0"},
    {string,    text,               "|",        "#B58900", always,      ""},
    {string,    time_date,          "%T",       "#B58900", always,      ""},
};

#endif
