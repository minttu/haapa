#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "acpi.h"
#include "config.h"
#include "result.h"
#include "util.h"

Result *battery_status(char *str) {
    Result *res;
    res = init_res();
    char file_location[128];

    sprintf(file_location, "%s%s/status", batpath, str);

    read_string(file_location, res->string, res);
    return res;
}

Result *battery_capacity(char *str) {
    Result *res;
    res = init_res();
    int capacity = 0;
    char file_location[128];

    sprintf(file_location, "%s%s/capacity", batpath, str);

    if (!read_int(file_location, &capacity, res)) {
        return res;
    }

    res->max = 100;
    res->value = (int)capacity;

    sprintf(res->string, "%i%%", capacity);

    return res;
}

Result *battery_time(char *str) {
    Result *res;
    res = init_res();

    int voltage = 0;
    int power = 0;
    int energy = 0;
    int energy_full = 0;
    int capacity = 0;
    int capacity_full = 0;
    int rate = 0;

    char status[128];
    char file_location[128];

    sprintf(file_location, "%s%s/voltage_now", batpath, str);

    if (!read_int(file_location, &voltage, res)) {
        return res;
    }

    sprintf(file_location, "%s%s/power_now", batpath, str);

    if (!read_int(file_location, &power, res)) {
        return res;
    }

    sprintf(file_location, "%s%s/energy_now", batpath, str);

    if (!read_int(file_location, &energy, res)) {
        return res;
    }

    sprintf(file_location, "%s%s/energy_full", batpath, str);

    if (!read_int(file_location, &energy_full, res)) {
        return res;
    }

    sprintf(file_location, "%s%s/status", batpath, str);

    if (!read_string(file_location, status, res)) {
        return res;
    }

    voltage /= 1000;
    power /= 1000;
    energy /= 1000;
    energy_full /= 1000;

    capacity = energy * 1000 / voltage;
    capacity_full = energy_full * 1000 / voltage;
    rate = power * 1000 / voltage;

    if (rate <= 0.01) {
        res->hidden = 1;
    } else {
        if(!strcmp(status, "Discharging")) {
            res->value = 3600 * capacity / rate;
        } else {
            res->value = 3600 * (capacity_full - capacity) / rate;
        }
    }

    return res;
}

int bat_islow(char *str) {
    FILE *f;
    int capacity = 0;
    char file_location[128];
    int val;
    file_location[0] = 0;
    strcat(file_location, batpath);
    strcat(file_location, str);
    strcat(file_location, "/");
    strcat(file_location, "capacity");

    f = fopen(file_location, "r");

    if (f == NULL) {
        return 0;
    }

    val = fscanf(f, "%i", &capacity);
    fclose(f);

    if (val == EOF) {
        return 0;
    }

    if (capacity < 20) {
        return 1;
    }

    return 0;
}

int bat_exists(char *str) {
    char file_location[128];
    struct stat s;

    sprintf(file_location, "%s%s/", batpath, str);
    stat(file_location, &s);

    return S_ISDIR(s.st_mode);
}

Result *cpu_temp(char *str) {
    Result *res;
    res = init_res();
    int temp = 0;

    if (!read_int("/sys/class/thermal/thermal_zone0/temp", &temp, res)) {
        return res;
    }

    res->value = (int)temp / 1000;
    sprintf(res->string, "%i°C", temp / 1000);

    return res;
}

int if_cpu_temp(char *str) {
    struct stat s;
    stat("/sys/class/thermal/thermal_zone0/", &s);
    return S_ISDIR(s.st_mode);
}
