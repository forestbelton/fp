OFILES := $(OFILES:%=../%)
CFLAGS += -I../include

.PHONY: all clean

all: fp-calc fp-repr

fp-calc: fp-calc.y
	bison -d fp-calc.y -o fp-calc.c
	$(CC) $(CFLAGS) $(OFILES) $(LDFLAGS) fp-calc.c -o $@
  
fp-repr : ../src/misc.c fp-repr.c
	$(CC) $(CFLAGS) ../src/misc.c fp-repr.c -o $@

clean:
	rm -rf $(OFILES) fp-calc.h fp-calc.c fp-calc fp-repr
