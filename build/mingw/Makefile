srcdir=../../src
prefix=/usr/local

PROGRAM=hpgs.exe
LIBRARY=libhpgs.a
OBJ=o
CC=gcc
STRIP=strip
LNS=ln -s

COPT=-g -O2
#COPT=-g
#COPT=-O3 -march=pentium4 -msse2 -mfpmath=sse

CFLAGS=$(COPT) -Wall -I$(srcdir) -I/usr/local/include
LDFLAGS=
LIBS=-L/usr/local/lib -lpng -lzdll -lm -liconv

AR=ar
ARFLAGS=cq

include $(srcdir)/include.mak
