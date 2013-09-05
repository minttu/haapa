include config.mk

.PHONY: default all clean

default: deps haapa
all: default

haapa:
	$(CC) -o haapa $(FILES) $(CFLAGS) $(LIBS)

clean:
	-rm -f src/*.o
	-rm -f haapa

deps:

ifeq ($(wildcard $(LIB_PATH)event.h),)
	@echo "REQUIRED libevent not found!"
	@exit 1
else
	@echo "REQUIRED libevent found"
	$(eval FILES += src/haapa.c src/proc.c src/result.c src/time.c src/battery.c src/network.c src/exec.c src/format.c src/output.c src/x256.c)
endif

ifeq ($(wildcard $(LIB_PATH)mpd/client.h),)
	@echo "OPTIONAL libmpdclient not found"
else
	@echo "OPTIONAL libmpdclient found"
	$(eval FILES += src/mpd.c)
	$(eval LIBS += -lmpdclient)
	$(eval CFLAGS += -DINCLUDE_MPD)
endif

ifeq ($(wildcard $(LIB_PATH)iwlib.h),)
	@echo "OPTIONAL iwlib not found"
else
	@echo "OPTIONAL iwlib found"
	$(eval FILES += src/wireless.c)
	$(eval LIBS += -liw)
	$(eval CFLAGS += -DINCLUDE_IWLIB)
endif

ifeq ($(wildcard $(LIB_PATH)alsa/asoundlib.h),)
	@echo "OPTIONAL alsa not found"
else
	@echo "OPTIONAL alsa found"
	$(eval FILES += src/alsa.c)
	$(eval LIBS += -lasound)
	$(eval CFLAGS += -DINCLUDE_ALSA)
endif

ifeq ($(wildcard $(LIB_PATH)X11/Xlib.h),)
	@echo "OPTIONAL Xlib not found"
else
	@echo "OPTIONAL Xlib found"
	$(eval FILES += src/output_x.c)
	$(eval LIBS += -lX11)
	$(eval CFLAGS += -DINCLUDE_XLIB)
endif

test:
	@./haapa -o