## -*- Mode: Makefile; -*-                                             
##
## Makefile for building the rosie custom version of lpeg
##
## © Copyright IBM Corporation 2016, 2017, 2018.
## LICENSE: MIT License (https://opensource.org/licenses/mit-license.html)
## AUTHOR: Jamie A. Jennings

REPORTED_PLATFORM=$(shell (uname -o || uname -s) 2> /dev/null)
ifeq ($(REPORTED_PLATFORM), Darwin)
PLATFORM=macosx
else ifeq ($(REPORTED_PLATFORM), GNU/Linux)
PLATFORM=linux
else
PLATFORM=none
endif

LIBNAME = lpeg
LUADIR = ../lua/

COPT = -DLPEG_DEBUG -O2
FILES = rcap.o rbuf.o lpvm.o lpcap.o lptree.o lpcode.o lpprint.o lpsave.o

ifeq ($(PLATFORM), macosx)
CC= cc
DLLFLAGS = -bundle -undefined dynamic_lookup
else
CC= gcc
DLLFLAGS = -shared -fPIC
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
        -Wno-missing-declarations \


CFLAGS = -fvisibility=hidden $(CWARNS) $(COPT) -std=c99 -I$(LUADIR)/include -fPIC

default: lpeg.so

lpeg.so: $(FILES)
	env $(CC) $(DLLFLAGS) $(FILES) -o lpeg.so

none:
	@echo "Your platform was not recognized.  Please do 'make PLATFORM', where PLATFORM is one of these: $(PLATFORMS)"

.PHONY: windows
windows:
	@echo Windows installation not yet supported.

.PHONY: test
test: test.lua re.lua lpeg.so
	./test.lua

.PHONY: clean
clean:
	rm -f $(FILES) lpprint.o lpeg.so


lpcap.o: lpcap.c lpcap.h rbuf.c rbuf.h rcap.c rcap.h lptypes.h rpeg.h
lpcode.o: lpcode.c lptypes.h lpcode.h lptree.h lpvm.h lpcap.h
lpprint.o: lpprint.c lptypes.h lpprint.h lptree.h lpvm.h lpcap.h
lptree.o: lptree.c lptypes.h lpcap.h lpcode.h lptree.h lpvm.h lpprint.h rpeg.h
lpvm.o: lpvm.c lpcap.h lptypes.h lpvm.h lpprint.h lptree.h
rbuf.o: rbuf.c rbuf.h
lpsave.o: lpsave.c lptypes.h lpsave.h lptree.h lpvm.h lpcap.h

