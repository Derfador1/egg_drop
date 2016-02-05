
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

profile:CFLAGS+=-pg
profile:LDFLAGS+=-pg
profile:egg_drop

egg_drop: egg_drop.o egg.o

.PHONY: clean debug profile

clean:
	rm egg_drop *.o

debug: CFLAGS+=-g
debug: egg_drop
