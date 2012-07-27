CFILES := src/add.c src/sub.c src/misc.c src/mul.c src/div.c src/abs.c \
	src/constants.c src/poly.c src/log.c src/sqrt.c src/agm.c
OFILES := $(CFILES:.c=.o)

CFLAGS := -Iinclude -Wall -Wextra -std=c99 -pedantic -O2 -Wno-unused-parameter

.PHONY : clean

check : $(OFILES)
	gcc $(CFLAGS) test/driver.c $(OFILES) -o test/driver
	tools/fpp test/add.c | gcc -xc - $(CFLAGS) -c -o test/add.o
	gcc test/add.o $(OFILES) -o test/add
	tools/fpp test/mul.c | gcc -xc - $(CFLAGS) -c -o test/mul.o
	gcc test/mul.o $(OFILES) -o test/mul
	tools/fpp test/print.c | gcc -xc - $(CFLAGS) -c -o test/print.o
	gcc test/print.o $(OFILES) -o test/print
	tools/fpp test/sqrt.c | gcc -xc - $(CFLAGS) -c -o test/sqrt.o
	gcc test/sqrt.o $(OFILES) -lm -o test/sqrt

tools : fp-repr fp-calc

fp-repr : src/misc.c
	gcc $(CFLAGS) tools/fp-repr.c src/misc.c -o tools/fp-repr

fp-calc : $(OFILES) tools/fp-calc.y
	bison -y tools/fp-calc.y -o tools/fp-calc.c
	gcc $(CFLAGS) $(OFILES) -DVERSION=\"$(shell git rev-parse HEAD)\" tools/fp-calc.c -o tools/fp-calc

%.o : %.c fp-repr
	tools/fpp $< | gcc -xc - $(CFLAGS) -c -o $@

clean :
	rm -rf $(OFILES) test/sqrt test/sqrt.o test/mul test/mul.o test/add test/add.o test/print test/print.o test/driver test/driver.exe tools/fp-repr tools/fp-repr.exe tools/fp-calc tools/fp-calc.c
