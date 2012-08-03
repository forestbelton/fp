CFILES  := add.c sub.c misc.c mul.c div.c abs.c constants.c poly.c log.c \
 sqrt.c agm.c compare.c
OFILES  := $(CFILES:.c=.o)

.PHONY: clean

libfp.a: $(OFILES)
	ar rcs libfp.a $(OFILES)

%.o: %.c
	$(FPP) $< | gcc -xc - $(CFLAGS) -c -o $@

clean:
	rm -rf libfp.a $(OFILES)
