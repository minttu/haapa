#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include "output.h"

static Display *dpy;
static int hasinit = 0;

void output_x(char *str) {
    if (hasinit == 0) {
        if (!(dpy = XOpenDisplay(NULL))) {
            fprintf(stderr, "cannot open display.\n");
            exit(1);
        }

        hasinit = 1;
    }

    XStoreName(dpy, DefaultRootWindow(dpy), str);
    XSync(dpy, False);
}