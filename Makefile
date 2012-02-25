CFILES := src/add.c src/sub.c src/misc.c src/mul.c src/div.c src/abs.c src/constants.c src/poly.c
OFILES := $(CFILES:.c=.o)

CFLAGS := -Iinclude -Wall -Wextra -std=c99 -pedantic -O2 -Wno-unused-parameter

.PHONY : clean

check : $(OFILES) tools
	gcc $(CFLAGS) test/driver.c $(OFILES) -o test/driver

tools : fp-repr

fp-repr : $(OFILES)
	gcc $(CFLAGS) tools/fp-repr.c $(OFILES) -o tools/fp-repr

%.o : %.c
	gcc $< $(CFLAGS) -c -o $@

clean :
	rm -rf $(OFILES) test/driver test/driver.exe tools/fp-repr tools/fp-repr.exe
