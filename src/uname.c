#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/utsname.h>

#include "uname.h"
#include "config.h"
#include "result.h"

Result *get_uname(char *str) {
    Result *res;
    int i;
    struct utsname unameData;
    res = init_res();

    if(uname(&unameData)!=0) {
        res->error=1;
        return res;
    }

    for(i = 0; i < strlen(str); i++) {
        if(i>0)
            strcat(res->string, " ");
        switch(str[i]) {
            case 'n':
                strcat(res->string, unameData.nodename);
                break;
            case 's':
                strcat(res->string, unameData.sysname);
                break;
            case 'r':
                strcat(res->string, unameData.release);
                break;
            case 'v':
                strcat(res->string, unameData.version);
                break;
            case 'a':
                strcat(res->string, unameData.sysname);
                strcat(res->string, " ");
                strcat(res->string, unameData.nodename);
                strcat(res->string, " ");
                strcat(res->string, unameData.release);
                strcat(res->string, " ");
                strcat(res->string, unameData.version);
                break;
            default: break;
        }
    }

    return res;
}