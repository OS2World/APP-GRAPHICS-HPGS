#
# i18n makefile
#
dep=no

include ../include.mak

ALLPOTSOURCES=$(addprefix ../, $(LIBCSOURCES) $(MAINCSOURCES))
POTFILE = hpgs.pot
POFILES=$(addprefix hpgs_, $(addsuffix .po, $(POLANGS)))

$(POTFILE): $(ALLPOTSOURCES)
	xgettext --keyword=hpgs_i18n --keyword=hpgs_i18n_n:1,2 -o $@ $^

hpgs_%.po: $(POTFILE)
	if test -f $@; then msgmerge -U $@ $<; else msginit -l $*.UTF-8 -i $< -o $@; fi

pot: $(POTFILE)

update-po: $(POFILES)
