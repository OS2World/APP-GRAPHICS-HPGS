srcdir=../../src
prefix=/sw
libsfx=lib

PROGRAM=hpgs
SLIB=libhpgs$(VERSION).dylib
SLIBALIAS1=libhpgs$(MVERSION).dylib
SLIBALIAS2=libhpgs.dylib
OBJ=o
CC=gcc
STRIP=strip
LNS=ln -sf

COPT=-g -O2
#COPT=-g
#COPT=-O3 -march=pentium4 -msse2 -mfpmath=sse

CFLAGS=$(COPT) -Wall -DNDEBUG -I$(srcdir) -I$(prefix)/include -DHPGS_SHARED -DHPGS_LIBSFX=\"$(libsfx)\" -DHPGS_DEFAULT_PREFIX=\"$(prefix)\" -DHPGS_HAVE_GETTEXT
LIBCFLAGS=-fPIC -DHPGS_BUILD_SLIB 
LDFLAGS=
LIBS=-L$(prefix)/$(slibsfx) -lpng -lintl -liconv -lz -lm -lpthread -ldl
SLD=gcc
SLDFLAGS=-dynamiclib -install_name $(prefix)/$(slibsfx)/$(SLIBALIAS1)

EXTRA_INSTALL_RULES=install-po

include $(srcdir)/include.mak
