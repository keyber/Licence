#include <stdio.h>
#include <stdlib.h>
#include "histogram.h"
#include "etire.h"
#include "pgm.h"

int main(int argc, char **argv) {
	if(argc==1){
		fprintf(stderr, "arg requis");
		return 1;
	}
	int w, h;
	unsigned char* buf = readpgm(argv[1], &w, &h);

	int size = w*h;

	int histo [256];
	histogramme(histo, buf, size);

	if(argc==2){
		affiche_histo(histo);
	}

	if(argc==3){
//		affiche_histo(histo);

//		printf("\n\n\n\n\n");

		int table [256];
		etire(table, histo);

		unsigned char* dst = malloc(sizeof(char) * size);

		applique(buf, dst, size, table);


//		affiche_histo(histo);

		int histoCopy [256];
		histogramme(histoCopy, dst, size);
		printf("\n\n\n\n\n");
//		affiche_histo(histoCopy);

		seuille(dst, dst, size, 48,208);
		histogramme(histoCopy, dst, size);

		printf("\n\n\n\n\n");
//		affiche_histo(histoCopy);

		writepgm(argv[2], dst, w, h);
		//printf("%d\n", diff(histo, histoCopy));
	}

	free(buf);
	return 0;
}
