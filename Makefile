CFILES := src/add.c src/sub.c src/misc.c src/mul.c
OFILES := $(CFILES:.c=.o)

CFLAGS := -Iinclude -Wall -Wextra -std=c99 -pedantic -O2 -Wno-unused-parameter

.PHONY : clean

check : $(OFILES)
	gcc $(CFLAGS) test/driver.c $(OFILES) -o test/driver

%.o : %.c
	gcc $< $(CFLAGS) -c -o $@

clean :
	rm -rf $(OFILES)