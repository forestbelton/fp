CFILES  := src/add.c src/sub.c src/misc.c src/mul.c src/div.c src/abs.c \
	src/constants.c src/poly.c src/log.c src/sqrt.c src/agm.c src/compare.c
OFILES  := $(CFILES:.c=.o)
HEADERS := include/fp.h include/util.h

export CC     := gcc
export CFLAGS := -Iinclude -Wall -Wextra -std=c99 -pedantic -O2 \
  -Wno-unused-parameter

.PHONY: clean check tools-pre tools all

all: libfp.a check tools

libfp.a: tools/fp-repr $(OFILES)
	ar rcs libfp.a $(OFILES)

check: libfp.a
	cd test; $(MAKE)

# Avoid circular dependency
tools/fp-repr:
	cd tools; $(MAKE) fp-repr

tools: libfp.a
	cd tools; $(MAKE)

%.o: %.c $(HEADERS)
	tools/fpp $< | gcc -xc - $(CFLAGS) -c -o $@

clean:
	rm -rf libfp.a $(OFILES)
	cd test;  $(MAKE) clean
	cd tools; $(MAKE) clean
