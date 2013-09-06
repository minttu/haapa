VERSION = 1.0
LIB_PATH = /usr/include/
PREFIX = /usr/local
CC = gcc
CFLAGS = --std=gnu99 -Wall -O2
LIBS = -levent -lm
FILES = src/haapa.c src/proc.c src/result.c src/time.c src/acpi.c src/uname.c src/network.c src/exec.c src/format.c src/output.c src/x256.c