EXAMPLES = fac.c
BINARIES = $(EXAMPLES:%.c=%)

CFLAGS  += -I../include
LDFLAGS += -L../ -lfp

.PHONY : all clean

all: $(BINARIES)

clean:
	rm -rf $(BINARIES)

%: %.c
	$(FPP) $< | $(CC) -xc - $(CFLAGS) $(LDFLAGS) -o $@

