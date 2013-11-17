top_srcdir=../../../src
srcdir=$(top_srcdir)/test
prefix=/usr/local

CC=gcc
COPT=-g -O2
CFLAGS=$(COPT) -Wall -Werror -DHPGS_SHARED -I$(top_srcdir) -I$(srcdir)

EXEC=LD_LIBRARY_PATH=..
EXEC_VG=LD_LIBRARY_PATH=..; valgrind --leak-check=yes --show-reachable=yes

LIBS=-L.. -lhpgs -lpng -lm -ldl

OBJ=o

include $(srcdir)/include.mak
