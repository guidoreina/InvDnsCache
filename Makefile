CC=gcc
CFLAGS=-g -Wall -pedantic -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DNCURSES_WIDECHAR -Wno-format -Wlong-long -std=c99

LDFLAGS=
LIBS=

MAKEDEPEND=${CC} -MM
PROGRAM=inv_dns_cache

OBJS =	InvDnsCache/dnscache.o InvDnsCache/main.o

DEPS:= ${OBJS:%.o=%.d}

all: $(PROGRAM)

${PROGRAM}: ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} ${LIBS} ${OBJS} -o $@

clean:
	rm -f ${PROGRAM} ${OBJS} ${DEPS}

${OBJS} ${DEPS} ${PROGRAM} : Makefile

.PHONY : all clean

%.d : %.c
	${MAKEDEPEND} ${CFLAGS} $< -MT ${@:%.d=%.o} > $@

%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $<

-include ${DEPS}
