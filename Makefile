.PHONY: all infocoll clean

APP     = infocoll
CC      = gcc
CFLAGS += -std=c11
CFLAGS += -Wall
CFLAGS += -g -pedantic
CFLAGS += $(shell pkg-config --cflags jansson)
LIBS   += $(shell pkg-config --libs jansson)

SRCS   := $(wildcard *.c)

all: $(APP)

$(APP):
	mkdir -p bin
	@$(CC) $(CFLAGS) $(LIBS) -I. -o bin/$@ ${SRCS}


clean:
	rm -r bin/$(APP)
	rmdir bin
