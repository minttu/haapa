#ifndef CONFIG_H
#define CONFIG_H

#include "modules.h"
#include "format.h"
#include "output.h"

static Format *(* const formatter)() = format_plain;
static void (* const outputter)(char *str) = output_plain;
static const int interval = 1;							/* time in seconds between ticks */
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
    {string,    text,               "\u266B",   "#BBDD64", mpd_exists, ""},
    {string,    mpd_smart,          " - ",      "#BBDD64", mpd_exists, ""},
    {timeconv,  mpd_sels,           "",         "#BBDD64", mpd_exists, ""},
    {string,    text,               "/",        "#BBDD64", mpd_exists, ""},
    {timeconv,  mpd_slen,           "",         "#BBDD64", mpd_exists, ""},
#endif
#ifdef INCLUDE_ALSA
    {string,    text,               "\u266B",   "#BBDD64", always,      ""},
    {bar,       alsa_volume,        "",         "#BBDD64", alsa_nmuted, ""},
    {string,    text,               "muted",    "#BBDD64", alsa_muted,  ""},
#endif
#ifdef INCLUDE_IWLIB
    {string,    text,               "\u21CB",   "#5F9F74", always,      ""},
    {string,    wireless_essid,     "wlan0",    "#5F9F74", net_ifup,    "wlan0"},
    {percent,   wireless_quality,   "wlan0",    "#5F9F74", net_ifup,    "wlan0"},
    {string,    network_ip,         "wlan0",    "#5F9F74", net_ifup,    "wlan0"},
    {string,    text,               "down",     "#FF0000", net_ifdown,  "wlan0"},
#endif
    {sizeconv,       fs_free,            "/","#00FF00", always,      ""},
    {sizeconv,       fs_used,            "/","#00FF00", always,      ""},
    {sizeconvi,       fs_free,            "/","#00FF00", always,      ""},
    {sizeconvi,       fs_used,            "/","#00FF00", always,      ""},
#ifndef ASDF
    {string,    text,               "\u2764",   "#B94557", always,      ""},
    {bar,       proc_cpu,           "",         "#B94557", always,      ""},
    {string,    text,               "\u2263",   "#B28D4C", always,      ""},
    {bar,       proc_memory,        "",         "#B28D4C", always,      ""},
    {string,    text,               "\u2607",   "#9933CC", bat_exists,  "BAT0"},
    {string,    battery_status,     "BAT0",     "#9933CC", bat_exists,  "BAT0"},
    {bar,       battery_capacity,   "BAT0",     "#9933CC", bat_exists,  "BAT0"},
    {string,    text,               "|",        "#FFFFFF", always,      ""},
    {string,    time_date,          "%T",       "#FFFFFF", always,      ""},
#endif
};

#endif
