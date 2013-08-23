LIBS = -lm -levent
CC = gcc
CFLAGS = -Wall -O2 --std=gnu99 -g
LIBS = -lm -levent
FILES = haapa.c

.PHONY: default all clean

default: args haapa
all: default

haapa: $(FILES)
	$(CC) $(CFLAGS) $(LIBS) $(FILES) -o haapa

clean:
	-rm -f *.o
	-rm -f haapa

args:
	$(eval FILES += $(ADD_FILE))
	$(eval LIBS += $(ADD_LIB))