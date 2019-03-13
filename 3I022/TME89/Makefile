CFLAGS = `inrinfo --cflags` `pkg-config glib-2.0 --cflags` -I. -g
LDLIBS = `inrinfo --libs` `pkg-config glib-2.0 --libs`

all: split merge

# TME 8
split: split.o utils.o mainsplit.o predicats.o segment.o
split.o utils.o mainsplit.o predicats.o segment.o: splitmerge.h

# TME 9
merge: mainmerge.o split.o utils.o predicats.o merge.o segment.o
mainmerge.o merge.o: splitmerge.h

clean:
	$(RM) split.o creer_region.o utils.o mainsplit.o predicats.o segment.o
	$(RM) merge.o mainmerge.o voisins.o 

cleanall: clean
	$(RM) split merge


