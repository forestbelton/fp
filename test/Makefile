CFILES  := add.c print.c mul.c driver.c sqrt.c
TESTS   := $(CFILES:.c=)
LDFLAGS += -lm

.PHONY: clean all

all: $(TESTS)

% : %.c
	$(CC) -I../include $(CFLAGS) $(OFILES:%=../%) $< $(LDFLAGS) -o $@

clean:
	rm -rf $(TESTS)
