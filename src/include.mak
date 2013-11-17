#
# boiler plate portion of makefile.
#
ifeq ($(devel_prefix),)
devel_prefix=$(prefix)
endif

ifeq ($(libsfx),)
libsfx=lib
endif

ifeq ($(slibsfx),)
slibsfx=$(libsfx)
endif

LIBCSOURCES =	hpgsbase.c \
		hpgsi18n.c \
		hpgsglobal.c \
		hpgsistream.c \
		hpgsostream.c \
		hpgszostream.c \
		hpgsbbox.c \
		hpgsmatrix.c \
		hpgsfont.c \
		hpgsdevices.c \
		hpgsreader.c \
		hpgscharacter.c \
		hpgslexer.c \
		hpgspe.c \
		hpgspen.c \
		hpgssetup.c \
		hpgstransform.c \
		hpgspath.c \
		hpgslabel.c \
		hpgsgstate.c \
		hpgspaint.c \
		hpgspaintpath.c \
		hpgspaintimage.c \
		hpgsscanline.c \
		hpgsbezier.c \
		hpgsimage.c \
		hpgsimagerop.c \
		hpgspcl.c \
		hpgspjl.c \
                hpgsrop.c

LIBHEADERS =    hpgs.h \
                hpgsmutex.h \
                hpgsplugin.h

MAINCSOURCES =	hpgs.c

MKROPCSOURCES =  hpgsmkrop.c

#
# if you add a language here, go to $(srcdir)/po and issue
#
# msginit -i hpgs.pot -o <lang>.po
#
POLANGS =  de

LIBOBJS = $(addsuffix .$(OBJ), $(basename $(LIBCSOURCES)))
MAINOBJS = $(addsuffix .$(OBJ), $(basename $(MAINCSOURCES)))
MKROPOBJS = $(addsuffix .$(OBJ), $(basename $(MKROPCSOURCES)))

OBJS=$(LIBOBJS) $(MAINOBJS) $(MKROPOBJS)

MVERSION=$(shell awk '/^\#define HPGS_(MAJOR|MINOR)_VERSION/ {printf(".%s",$$3);}' $(srcdir)/hpgs.h)
VERSION=$(shell awk '/^\#define HPGS_(MAJOR|MINOR|PATCH)_VERSION/ {printf(".%s",$$3);} /^\#define HPGS_EXTRA_VERSION/ {printf("%s",$$3);}' $(srcdir)/hpgs.h)

%.depend:  $(srcdir)/%.c
	$(CC) $(LIBCFLAGS) $(CFLAGS) -M $< > $@

%.$(OBJ): $(srcdir)/%.c
	$(CC) $(LIBCFLAGS) $(CFLAGS) -c $< -o $@

all: $(PROGRAM)

hpgs.depend:  $(srcdir)/hpgs.c
	$(CC) $(CFLAGS) -M $< > $@

hpgs.$(OBJ): $(srcdir)/hpgs.c
	$(CC) $(CFLAGS) -c $< -o $@

pre: $(srcdir)/hpgsrop.c

hpgsmkrop.$(OBJ): $(srcdir)/hpgsmkrop.c
	$(CC) $(CFLAGS) -c $< -o $@

hpgsmkrop: $(MKROPOBJS)
	$(CC) $(LDFLAGS) $(MKROPOBJS) -o $@

$(srcdir)/hpgsrop.c: $(srcdir)/hpgsrop.dat $(srcdir)/hpgsmkrop.c
	make dep=no hpgsmkrop
	./hpgsmkrop $< $@

docs:  $(PROGRAM) $(srcdir)/hpgs.doxycfg
	make -C $(srcdir)/../doc/images
	./$(PROGRAM) --help 2> $(srcdir)/hpgs-args.txt
	cd $(srcdir); doxygen hpgs.doxycfg
	@echo "The doxygen documentation is now installed in:"
	@cd $(srcdir)/../doc/latex; echo `pwd`": LaTeX files."
	@cd $(srcdir)/../doc/html; echo `pwd`":  HTML  files."

$(PROGRAM): $(LIBRARY) $(SLIB) $(MAINOBJS)
	$(CC) $(LDFLAGS) $(MAINOBJS) $(LIBRARY) $(SLIB) $(LIBS) -o $@

ifneq ($(LIBRARY),)

$(LIBRARY): $(LIBOBJS)
	@rm -f $(LIBRARY)
	$(AR) $(ARFLAGS) $(LIBRARY) $(LIBOBJS)

endif

ifneq ($(SLIB),)

$(SLIB): $(LIBOBJS)
	rm -f $(SLIB) $(SLIBALIAS1) $(SLIBALIAS2)
	$(SLD) $(SLDFLAGS) $(LIBOBJS) $(LIBS) -o $@
	$(LNS) $(SLIB) $(SLIBALIAS1)
	$(LNS) $(SLIB) $(SLIBALIAS2)

endif

install: all $(EXTRA_INSTALL_RULES)
	cp $(PROGRAM) $(prefix)/bin
	if test "$(LIBRARY)"; then cp $(LIBRARY) $(prefix)/$(libsfx); fi
	if test "$(SLIB)"; then rm -f $(prefix)/$(slibsfx)/$(SLIB); cp $(SLIB) $(prefix)/$(slibsfx); fi
	if test "$(SLIB)"; then cd $(prefix)/$(slibsfx); $(LNS) $(SLIB) $(SLIBALIAS1); fi
	$(STRIP) $(prefix)/bin/$(PROGRAM)
	chmod 755 $(prefix)/bin/$(PROGRAM)

install-devel: install
	cp  $(addprefix $(srcdir)/, $(LIBHEADERS)) $(devel_prefix)/include
	cd $(devel_prefix)/include; chmod 644 $(LIBHEADERS)
	if test "$(SLIB)"; then cd $(devel_prefix)/$(libsfx); if test "$(prefix)/$(slibsfx)" = "$(devel_prefix)/$(libsfx)"; then $(LNS) $(SLIB) $(SLIBALIAS2); else $(LNS) $(prefix)/$(slibsfx)/$(SLIB) $(SLIBALIAS2); fi; fi

install-po:
	for lang in $(POLANGS); do mkdir -p $(prefix)/share/locale/$$lang/LC_MESSAGES; msgfmt -o $(prefix)/share/locale/$$lang/LC_MESSAGES/hpgs.mo $(srcdir)/po/hpgs_$$lang.po; done

clean:
	rm -f $(OBJS) $(PROGRAM) hpgsmkrop $(LIBRARY) $(SLIB) $(SLIBALIAS1) $(SLIBALIAS2) *~ *.bak .*~ .*.bak

distclean: clean
	rm -f  $(addsuffix .depend, $(basename $(OBJS)))

cvsclean: distclean
	rm -f  $(srcdir)/hpgsrop.c

#
# dependencies
#
ifneq ($(dep),no)
include $(addsuffix .depend, $(basename $(OBJS)))
endif
