CFILES  := add.c print.c mul.c driver.c sqrt.c
TESTS   := $(CFILES:.c=)
LDFLAGS += -L../ -lm -lfp

.PHONY: clean all

all: $(TESTS)

% : %.c
	$(CC) -I../include $(CFLAGS) $< $(LDFLAGS) -o $@

clean:
	rm -rf $(TESTS)
