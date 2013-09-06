include config.mk

.PHONY: default all clean install uninstall deps opts

default: deps opts haapa
all: default

src/config.h:
ifeq ($(wildcard src/config.h),)
	@echo "Creating $@ from src/config.def.h\n"
	@cp src/config.def.h $@
else
endif

haapa: src/config.h
	$(CC) -o haapa $(FILES) $(CFLAGS) $(LIBS)

clean:
	-rm -f src/*.o
	-rm -f haapa

install:
ifeq ($(wildcard haapa),)
	@echo "Compile haapa first! (Just run make)"
else
	@echo Installing to $(PREFIX)
	@cp -f haapa $(PREFIX)
	@chmod 775 $(PREFIX)/haapa
endif

uninstall:
	@echo Uninstalling from $(PREFIX)
	@rm -f $(PREFIX)/haapa

opts:
	@echo ""
	@echo "CFLAGS:     $(CFLAGS)"
	@echo "LIBS:       $(LIBS)"
	@echo "FILES:      $(FILES)"
	@echo ""

deps:

ifeq ($(wildcard $(LIB_PATH)event.h),)
	@echo "REQUIRED libevent     not found!"
	@exit 1
else
	@echo "REQUIRED libevent     found"
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
	@echo "OPTIONAL iwlib        not found"
else
	@echo "OPTIONAL iwlib        found"
	$(eval FILES += src/wireless.c)
	$(eval LIBS += -liw)
	$(eval CFLAGS += -DINCLUDE_IWLIB)
endif

ifeq ($(wildcard $(LIB_PATH)alsa/asoundlib.h),)
	@echo "OPTIONAL alsa         not found"
else
	@echo "OPTIONAL alsa         found"
	$(eval FILES += src/alsa.c)
	$(eval LIBS += -lasound)
	$(eval CFLAGS += -DINCLUDE_ALSA)
endif

ifeq ($(wildcard $(LIB_PATH)X11/Xlib.h),)
	@echo "OPTIONAL Xlib         not found"
else
	@echo "OPTIONAL Xlib         found"
	$(eval FILES += src/output_x.c)
	$(eval LIBS += -lX11)
	$(eval CFLAGS += -DINCLUDE_XLIB)
endif

test:
	@./haapa -o