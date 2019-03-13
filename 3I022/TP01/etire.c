#include <stdio.h>
#include "etire.h"

int min(int a, int b){
	return a<b?a:b;
}

int max(int a, int b){
	return a>b?a:b;
}

/*
 * table indexée par ancienne couleur contient nouvelle couleur
 * calcule nouvel histogramme sans parcourir toute l'image
 */
void etire (int table[256], int his[256]){
	int imin=0;
	while (imin<256 && his[imin]==0) imin++;

	if(imin == 256){
		fprintf(stderr, "hist nul\n");
		return;
	}

	int imax=255;
	while (his[imax]==0) imax--;

	if(imin == imax){
		fprintf(stderr, "hist non etirable\n");
		return;
	}

	float facteur_dilatation = ((float)255) /  (imax - imin);

	int i=0;
	for (;i <= imin; ++i)
		table[i] = 0;
	for (; i < imax; ++i)
		table[i] = (int)((i-imin)*facteur_dilatation);
	for (; i < 256; ++i)
		table[i] = 255;

	int hOld[256];
	for (i = imin; i <= imax; ++i)
		hOld[i] = his[i];

	for (i = 0; i < 256; ++i)
		his[i] = 0;

	for (i = imin; i <= imax; ++i)
		his[table[i]] = hOld[i];
}

void applique (unsigned char* src, unsigned char* dst, int size, int table[256]){
	int i;
	for (i = 0; i < size; ++i) {
		dst[i]=table[src[i]];
	}
}


void seuille(unsigned char* src, unsigned char* dst, int size, unsigned char min, unsigned char max){
	int i;
	for (i = 0; i < size; ++i) {
		dst[i] = (src[i]<min)? 0 : (src[i]>max)? 255 : src[i];
	}
}
