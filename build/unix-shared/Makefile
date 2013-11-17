srcdir=../../src
prefix=/usr/local
libsfx=lib

PROGRAM=hpgs
SLIB=libhpgs.so$(VERSION)
SLIBALIAS1=libhpgs.so$(MVERSION)
SLIBALIAS2=libhpgs.so
OBJ=o
CC=gcc
STRIP=strip
LNS=ln -sf

COPT=-g -O2
#COPT=-g
#COPT=-O3 -march=pentium4 -msse2 -mfpmath=sse

CFLAGS=$(COPT) -Wall -I$(srcdir) -DHPGS_SHARED -DHPGS_LIBSFX=\"$(libsfx)\" -DHPGS_DEFAULT_PREFIX=\"$(prefix)\" -DHPGS_HAVE_GETTEXT
LIBCFLAGS=-fPIC -DHPGS_BUILD_SLIB 
LDFLAGS=
LIBS=-lpng -lm -lpthread -ldl
SLD=gcc
SLDFLAGS=-shared -Wl,-soname=$(SLIBALIAS1)

EXTRA_INSTALL_RULES=install-po

include $(srcdir)/include.mak
