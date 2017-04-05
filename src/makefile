LIBNAME = lpeg
LUADIR = ../lua/

ifdef LPEG_DEBUG
COPT = -DLPEG_DEBUG -g
FILES = rcap.o lpvm.o lpcap.o lptree.o lpcode.o lpprint.o
else
COPT = -O2
FILES = rcap.o lpvm.o lpcap.o lptree.o lpcode.o
endif

ifdef ROSIE_DEBUG
COPT += -DROSIE_DEBUG
endif

CWARNS = -Wall -Wextra -pedantic \
	-Waggregate-return \
	-Wcast-align \
	-Wcast-qual \
	-Wdisabled-optimization \
	-Wpointer-arith \
	-Wshadow \
	-Wsign-compare \
	-Wundef \
	-Wwrite-strings \
	-Wbad-function-cast \
	-Wdeclaration-after-statement \
	-Wmissing-prototypes \
	-Wnested-externs \
	-Wstrict-prototypes \
        -Wunreachable-code \


CFLAGS = $(CWARNS) $(COPT) -std=c99 -I$(LUADIR)/include -fPIC
CC = gcc

default:
	@echo "Please specify a platform to build for.  Choices are: linux, macosx"

# For Linux
linux:
	make lpeg.so "DLLFLAGS = -shared -fPIC"

# For Mac OS
macosx:
	make lpeg.so "DLLFLAGS = -bundle -undefined dynamic_lookup"

lpeg.so: $(FILES)
	env $(CC) $(DLLFLAGS) $(FILES) -o lpeg.so

$(FILES): makefile

test: test.lua re.lua lpeg.so
	./test.lua

clean:
	rm -f $(FILES) lpprint.o lpeg.so


lpcap.o: lpcap.c lpcap.h rbuf.c rbuf.h rcap.c rcap.h lptypes.h 
lpcode.o: lpcode.c lptypes.h lpcode.h lptree.h lpvm.h lpcap.h
lpprint.o: lpprint.c lptypes.h lpprint.h lptree.h lpvm.h lpcap.h
lptree.o: lptree.c lptypes.h lpcap.h lpcode.h lptree.h lpvm.h lpprint.h
lpvm.o: lpvm.c lpcap.h lptypes.h lpvm.h lpprint.h lptree.h
rcap.o: rcap.h rcap.c
#rbuf.o: rbuf.c rbuf.h

