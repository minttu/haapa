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

static const char *const alsa_channel = "Master";

static const Segment segments[] = {
#ifdef INCLUDE_MPD
    {string,    text,               "\u266A",   "#5F9F74", mpd_playing, ""},
    {string,    mpd_smart,          " - ",      "#FFFFFF", mpd_playing, ""},
    {timeconv,  mpd_sels,           "",         "#FFFFFF", mpd_playing, ""},
    {string,    text,               "/",        "#5F9F74", mpd_playing, ""},
    {timeconv,  mpd_slen,           "",         "#FFFFFF", mpd_playing, ""},
#endif
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
    {string,    text,               "\u2607",   "#9933CC", bat_exists,  "BAT0"},
    {string,    battery_status,     "BAT0",     "#9933CC", bat_exists,  "BAT0"},
    {bar,       battery_capacity,   "BAT0",     "#9933CC", bat_exists,  "BAT0"},
#ifdef INCLUDE_ALSA
    {string,    text,               "\u266B",   "#BBDD64", always,      ""},
    {percent,   alsa_volume,        "",         "#BBDD64", alsa_nmuted, ""},
    {string,    text,               "muted",    "#BBDD64", alsa_muted,  ""},
#endif
    {string,    text,               "|",        "#FFFFFF", always,      ""},
    {string,    time_date,          "%T",       "#FFFFFF", always,      ""},
};

#endif
