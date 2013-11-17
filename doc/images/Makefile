%.eps: %.fig
	fig2dev -L eps $< $@ 

%.png: %.eps
	sh ./eps2png.sh $< $@

FIGURES=clipper.fig scanline_0.fig scanline_n.fig


EPSFILES=$(addsuffix .eps, $(basename $(FIGURES)))
PNGFILES=$(addsuffix .png, $(basename $(FIGURES)))

all: eps png

clean:
	rm -rf *~ *.bak $(EPSFILES) $(PNGFILES)

eps: $(EPSFILES)

png: $(PNGFILES)