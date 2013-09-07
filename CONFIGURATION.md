Configuring
===========

Each segment is made up of 6 parts. **Output handler**, **output generator**, **generator arguments**, **color**, **conditions**, **condition arguments**. Having a color such as "#FF0000,#FFFFFF" will flash between the two.

**Output handlers**
-------------------

These handle how the generated content is displayed. Valid ones are: string, bar, percent and timeconv. Pretty self-explanatory.

**Output generators**
---------------------

| Name              | Arguments | Effect                                                    | Requires | Working |
| ----------------- | --------- | --------------------------------------------------------- | -------- | ------- |
| proc_load         | 0-3       | Returns average cpu load. 0: 1min 1: 5min 2: 15min 3: all |          | Yes     |
| proc_memory       |           | Returns memory usage                                      |          | Yes     |
| proc_cpu          |           | Returns cpu usage                                         |          | Yes     |
| proc_cpu_mhz      |           | Returns cpu MHz                                           |          | Yes     |
| proc_uptime       |           | Returns uptime as seconds                                 |          | Yes     |
| time_date         | strftime  | Returns date time formatted with                          |          | Yes     |
| battery_status    | battery   | Returns the status for the battery                        |          | Yes     |
| battery_capacity  | battery   | Returns the current capacity for the battery              |          | Yes     |
| cpu_temp          |           | Returns the temperature of the first cpu                  |          | Yes     |
| network_ip        | interface | Returns the IP for the interface                          |          | Yes     |
| exec              | command   | Executes the command and returns the output               |          | Yes     |
| get_uname         | a,s,n,r,v | Returns information, like the uname program does          |          | Yes     |
| fs_total          | path      | Returns total available space in (mounted) path           |          | Yes     |
| fs_free           | path      | Returns total free space in (mounted) path                |          | Yes     |
| fs_used           | path      | Returns total used space in (mounted) path                |          | Yes     |
| downspeed         | interface | Returns current download speed for the interface          |          | Yes     |
| upspeed           | interface | Returns current upload speed for the interface            |          | Yes     |
| wireless_essid    | interface | Returns the network's ESSID for the interface             | iwlib    | Yes     |
| wireless_ap_addr  | interface | Returns the access point's hardware address               | iwlib    | No      |
| wireless_freq     | interface | Returns the network's frequency for the interface         | iwlib    | Partial |
| wireless_chan     | interface | Returns the network's channel for the interface           | iwlib    | No      |
| wireless_bitrate  | interface | Returns the network's bitrate for the interface           | iwlib    | No      |
| wireless_quality  | interface | Returns the network's  signal strength  for the interface | iwlib    | Yes     |
| alsa_volume       | channel   | Returns the volume of the channel                         | alsa     | Yes     |
| mpd_vera          |           | Returns MPD's major version number                        | mpd      | Yes     |
| mpd_verb          |           | Returns MPD's middle version number                       | mpd      | Yes     |
| mpd_verc          |           | Returns MPD's minor version number                        | mpd      | Yes     |
| mpd_qv            |           | Returns MPD's queue version                               | mpd      | Yes     |
| mpd_ql            |           | Returns MPD's queue (playlist) length                     | mpd      | Yes     |
| mpd_spos          |           | Returns MPD's currently playing song's position in queue  | mpd      | Yes     |
| mpd_sels          |           | Returns MPD's currently playing song's elapsed seconds    | mpd      | Yes     |
| mpd_selms         |           | Returns MPD's currently playing song's elased milliseconds| mpd      | Yes     |
| mpd_sbrat         |           | Returns MPD's currently playing song's bit rate           | mpd      | Yes     |
| mpd_afsr          |           | Returns MPD's currently playing song's sample rate        | mpd      | Yes     |
| mpd_afbits        |           | Returns MPD's currently playing song's bit amount         | mpd      | Yes     |
| mpd_afchan        |           | Returns MPD's currently playing song's channel amount     | mpd      | Yes     |
| mpd_ur            |           | Returns MPD's currently playing song's uri (file name)    | mpd      | Yes     |
| mpd_artist        |           | Returns MPD's currently playing song's artist             | mpd      | Yes     |
| mpd_album         |           | Returns MPD's currently playing song's album              | mpd      | Yes     |
| mpd_title         |           | Returns MPD's currently playing song's title              | mpd      | Yes     |
| mpd_track         |           | Returns MPD's currently playing song's track number       | mpd      | Yes     |
| mpd_name          |           | Returns MPD's currently playing song's name               | mpd      | Yes     |
| mpd_date          |           | Returns MPD's currently playing song's name               | mpd      | Yes     |
| mpd_smart         | separator | MPD's current song as artist - name if possible, else uri | mpd      | Yes     |

**Conditions**
--------------

| Name              | Arguments | Effect                                                    | Requires | Working |
| ----------------- | --------- | --------------------------------------------------------- | -------- | ------- |
| net_ifup          | interface | Returns 1 if interface is up                              |          | Yes     |
| net_ifdown        | interface | Returns 1 if interface is down                            |          | Yes     |
| bat_exists        | battery   | Returns 1 if battery exists                               |          | Yes     |
| bat_islow         | battery   | Returns 1 if battery capacity is under 20%                |          | Yes     |
| if_cpu_temp       |           | Returns 1 if haapa can get the cpu temperature            |          | Yes     |
| alsa_muted        | channel   | Returns 1 if channel is muted                             | alsa     | Yes     |
| mpd_playing       |           | Returns 1 if mpd is playing                               | mpd      | Yes     |

**Global options**
------------------

| Name               | Arguments | Effect                                                    | Requires | Working |
| ------------------ | --------- | --------------------------------------------------------- | -------- | ------- |
| formatter          | format_*  | Possible values: plain, i3, i3_manual, dzen, xmobar, x256 |          | Yes     |
| outputter          | output_*  | Possible values: plain, ontop, x                          | x: Xlib  | Yes     |
| interval           | integer   | How often should haapa update, in seconds                 |          | Yes     |
| batpath            | path      | Path to where the systems batteries reside                |          | Yes     |
| segment_seperator  | string    | What string will seperate each segment in FORMAT_PLAIN    |          | Yes     |
| bar_format_unicode | integer   | How is the bar drawn. 0: no unicode, 1: vert 2: hori      |          | Yes     |
| bar_format         | string    | Whats aside the bar                                       |          | Yes     |
| bar_format_length  | integer   | How long are bars                                         |          | Yes     |
