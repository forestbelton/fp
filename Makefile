CFILES := src/add.c src/sub.c src/misc.c src/mul.c src/div.c src/abs.c \
	src/constants.c src/poly.c src/log.c
OFILES := $(CFILES:.c=.o)

CFLAGS := -Iinclude -Wall -Wextra -std=c99 -pedantic -O2 -Wno-unused-parameter

.PHONY : clean

check : $(OFILES)
	gcc $(CFLAGS) test/driver.c $(OFILES) -o test/driver

tools : fp-repr

fp-repr : src/misc.c
	gcc $(CFLAGS) tools/fp-repr.c src/misc.c -o tools/fp-repr

%.o : %.c tools
	tools/fpp $< | gcc -xc - $(CFLAGS) -c -o $@

clean :
	rm -rf $(OFILES) test/driver test/driver.exe tools/fp-repr tools/fp-repr.exe
