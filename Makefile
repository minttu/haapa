LIBS = -lm -levent
CC = gcc
CFLAGS = -Wall -O2 --std=gnu99 -g
LIBS = -lm -levent
FILES =

.PHONY: default all clean

default: warn
all: default

haapa:
	$(CC) -o haapa $(FILES) $(CFLAGS) $(LIBS)

clean:
	-rm -f src/*.o
	-rm -f haapa

args:
	$(eval FILES += $(ADD_FILE))
	$(eval LIBS += $(ADD_LIB))
	$(eval CFLAGS += $(ADD_CFLAG))

build_haapa: args haapa

warn:
	@echo "run ./build.sh instead"
