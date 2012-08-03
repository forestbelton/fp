CFILES  := src/add.c src/sub.c src/misc.c src/mul.c src/div.c src/abs.c \
	src/constants.c src/poly.c src/log.c src/sqrt.c src/agm.c src/compare.c
OFILES  := $(CFILES:.c=.o)
HEADERS := include/fp.h include/util.h

export CC     := gcc
export CFLAGS := -Iinclude -Wall -Wextra -std=c99 -pedantic -O2 \
  -Wno-unused-parameter

bindir     = /usr/bin
libdir     = /usr/lib
includedir = /usr/include

.PHONY: clean check tools all install

all: libfp.a tools

install: libfp.a tools/fpp
	install -C -m 755 tools/fpp $(bindir)/fpp
	install -C -m 644 libfp.a $(libdir)/libfp.a
	mkdir -p $(includedir)/fp
	install -C -m 644 include/fp/fp.h $(includedir)/fp/fp.h
	install -C -m 644 include/fp/util.h $(includedir)/fp/util.h

libfp.a: tools/fpp $(OFILES)
	ar rcs libfp.a $(OFILES)

# Avoid circular dependency
tools/fpp:
	cd tools; $(MAKE) fpp

tools: libfp.a
	cd tools; $(MAKE)

%.o: %.c
	tools/fpp $< | gcc -xc - $(CFLAGS) -c -o $@

clean:
	rm -rf libfp.a $(OFILES)
	cd tools; $(MAKE) clean
