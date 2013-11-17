top_srcdir=../../../src
srcdir=$(top_srcdir)/test
prefix=/usr/local

CC=gcc
COPT=-g -O2
CFLAGS=$(COPT) -Wall -Werror -I$(top_srcdir) -I$(srcdir)

EXEC=

LIBS=../libhpgs.a /mingw/lib/libfreetype.a -lpng -lzdll -lm -liconv

OBJ=o

include $(srcdir)/include.mak
