CFILES := src/add.c src/sub.c src/misc.c src/mul.c src/div.c src/abs.c \
	src/constants.c src/poly.c src/log.c src/sqrt.c src/agm.c src/compare.c
export CC     := gcc
export OFILES := $(CFILES:.c=.o)
export CFLAGS := -Iinclude -Wall -Wextra -std=c99 -pedantic -O2 -Wno-unused-parameter

.PHONY : clean

all : check tools

check : $(OFILES)
	cd test; $(MAKE)

# Avoid circular dependency
tools-pre :
	cd tools; $(MAKE) fp-repr

tools : $(OFILES)
	cd tools; $(MAKE)

%.o : %.c tools-pre
	tools/fpp $< | gcc -xc - $(CFLAGS) -c -o $@

clean:
	rm -rf $(OFILES)
	cd test;  $(MAKE) clean
	cd tools; $(MAKE) clean
