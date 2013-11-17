TESTSOURCES=	matrix_test.c \
                font_test.c

%.depend: $(srcdir)/%.c
	$(CC) -M $(CFLAGS) $< > $@

%.exe: $(srcdir)/%.c
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

%-test: %.exe
	$(EXEC) ./$<

%-vg: %.exe
	$(EXEC_VG) ./$<


TESTTARGETS=$(addsuffix -test, $(basename $(TESTSOURCES)))
VGTESTTARGETS=$(addsuffix -vg, $(basename $(TESTSOURCES)))

all: hpgslib $(TESTTARGETS)

vg: hpgslib $(VGTESTTARGETS)

foo:


hpgslib: foo
	make -C ..
