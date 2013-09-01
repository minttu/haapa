Configuring
===========

Each segment is made up of 6 parts. **Output handler**, **output generator**, **generator arguments**, **color**, **conditions**, **condition arguments**.

**Output handlers**
-------------------

These handle how the generated content is displayed. Valid ones are: string, bar, percent and timeconv. Pretty self-explanatory.

**Output generators**
---------------------

| Name              | Arguments | Effect                                                    | Requires | Working |
| ----------------- | --------- | --------------------------------------------------------- | -------- | ------- |
| proc_load         | 0-3       | Returns average cpu load. 0: 1min 1: 5min 2: 15min 3: all |          | Yes     |
| proc_memory       |           | Returns memory usage.                                     |          | Yes     |
| proc_cpu          |           | Returns cpu usage.                                        |          | Yes     |
| proc_uptime       |           | Returns system uptime in x days, HH:MM:SS format.         |          | Yes     |
| time_date         | strftime  | Returns date time formatted with                          |          | Yes     |
| battery_status    | battery   | Returns the status for the battery                        |          | Yes     |
| battery_capacity  | battery   | Returns the current capacity for the battery              |          | Yes     |
| network_ip        | interface | Returns the IP for the interface                          |          | Yes     |
| exec              | command   | Executes the command and returns the output               |          | Yes     |
| wireless_essid    | interface | Returns the networks ESSID for the interface              | iwlib    | Yes     |
| alsa_volume       | channel   | Returns the volume of the channel                         | alsa     | No      |
| mpd_vera          |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_verb          |           | Returns mpd's middle version number                       | mpd      | Yes     |
| mpd_verc          |           | Returns mpd's minor version number                        | mpd      | Yes     |
| mpd_qv            |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_ql            |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_spos          |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_sels          |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_selms         |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_sbrat         |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_afsr          |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_afchan        |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_afsr          |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_uri           |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_artist        |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_album         |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_afsr          |           | Returns mpd's major version number                        | mpd      | Yes     |
| mpd_afsr          |           | Returns mpd's major version number                        | mpd      | Yes     |

**Conditions**
--------------

| Name              | Arguments | Effect                                                    | Requires | Working |
| ----------------- | --------- | --------------------------------------------------------- | -------- | ------- |
| net_ifup          | interface | Returns 1 if interface is up                              |          | Yes     |
| net_ifdown        | interface | Returns 1 if interface is down                            |          | Yes     |
| bat_exists        | battery   | Returns 1 if battery exists                               |          | Yes     |
| alsa_muted        | channel   | Returns 1 if channel is muted                             | alsa     | No      |
| mpd_playing       |           | Returns 1 if mpd is playing                               | mpd      | Yes     |

**Global options**
------------------

| Name              | Arguments | Effect                                                    | Requires | Working |
| ----------------- | --------- | --------------------------------------------------------- | -------- | ------- |
| output_format     | FORMAT_*  | FORMAT_PLAIN: plain output. FORMAT_I3: i3bar formatted    |          | Yes     |
| output_ontop      | boolean   | Should haapa print ontop of itself, erasing the previous  |          | Yes     |
| interval          | integer   | How often should haapa update, in seconds                 |          | Yes     |
| batpath           | path      | Path to where the systems batteries reside                |          | Yes     |
| segment_seperator | string    | What string will seperate each segment in FORMAT_PLAIN    |          | Yes     |
