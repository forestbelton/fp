export CC     := gcc
export CFLAGS := -I$(shell pwd)/include -L$(shell pwd)/src -Wall -Wextra -std=c99 \
  -pedantic -O2 -Wno-unused-parameter
export FPP    := $(shell pwd)/tools/fpp

bindir     = /usr/bin
libdir     = /usr/lib
includedir = /usr/include

.PHONY: clean tools all install ex

all: src/libfp.a tools ex

install: src/libfp.a tools/fpp
	install -C -m 755 tools/fpp   $(bindir)/fpp
	install -C -m 644 src/libfp.a $(libdir)/libfp.a
	mkdir -p $(includedir)/fp
	install -C -m 644 include/fp/fp.h $(includedir)/fp/fp.h
	install -C -m 644 include/fp/util.h $(includedir)/fp/util.h

src/libfp.a: tools/fpp
	cd src; $(MAKE)

# Avoid circular dependency
tools/fpp:
	cd tools; $(MAKE) fpp

tools: src/libfp.a
	cd tools; $(MAKE)

ex: src/libfp.a
	cd ex; $(MAKE)

clean:
	cd src;   $(MAKE) clean
	cd ex;    $(MAKE) clean
	cd tools; $(MAKE) clean
