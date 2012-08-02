CFLAGS  += -I../include -Wno-implicit-function-declaration -Wno-unused-function
LDFLAGS += -L../ -lfp

.PHONY: all clean

all: fp-calc fp-repr fpp

fp-calc: fp-calc.y fp-calc.l
	bison -d fp-calc.y -o fp-calc.c
	flex -o fp-calc.lex.c fp-calc.l
	$(CC) $(CFLAGS) fp-calc.lex.c fp-calc.c $(LDFLAGS) -o $@

fpp : fpp.l ../src/misc.c
	flex -o fpp.lex.c fpp.l
	$(CC) $(CFLAGS) fpp.lex.c ../src/misc.c -o $@
  
fp-repr : ../src/misc.c fp-repr.c
	$(CC) $(CFLAGS) ../src/misc.c fp-repr.c -o $@

clean:
	rm -rf fp-calc.h fp-calc.lex.c fp-calc.c fp-calc fp-repr fpp.lex.c fpp
