CFLAGS  += -I../include -Wno-implicit-function-declaration -Wno-unused-function
LDFLAGS += -L../ -lfp

.PHONY: all clean

all: fp-calc fp-repr

fp-calc: fp-calc.y fp-calc.l
	bison -d fp-calc.y -o fp-calc.c
	flex -o fp-calc.lex.c fp-calc.l
	$(CC) $(CFLAGS) fp-calc.lex.c fp-calc.c $(LDFLAGS) -o $@
  
fp-repr : ../src/misc.c fp-repr.c
	$(CC) $(CFLAGS) ../src/misc.c fp-repr.c -o $@

clean:
	rm -rf fp-calc.h fp-calc.lex.c fp-calc.c fp-calc fp-repr
