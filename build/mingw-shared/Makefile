srcdir=../../src
prefix=$(subst \,/,$(PROGRAMFILES))/ev-i
devel_prefix=/usr/local

PROGRAM=hpgs.exe
SLIB=hpgs$(VERSION).dll
SLIBALIAS1=hpgs$(MVERSION).dll
SLIBALIAS2=hpgs.dll
slibsfx=bin
OBJ=o
CC=gcc
STRIP=strip
LNS=ln -sf

COPT=-g -O2
#COPT=-g
#COPT=-O3 -march=pentium4 -msse2 -mfpmath=sse

CFLAGS=$(COPT) -Wall -DHPGS_SHARED -I$(srcdir) -I/mingw/gnome/include
LIBCFLAGS=-DHPGS_BUILD_SLIB -DHPGS_HAVE_GETTEXT
LDFLAGS=
LIBS=-L/mingw/gnome/lib -lpng -lzdll -lm -liconv -lintl

SLD=gcc
SLDFLAGS=-shared -Wl,-dll -Wl,-soname=$(SLIBALIAS1)

include $(srcdir)/include.mak
