#include <stdio.h>
#include <stdlib.h>

void histogramme (int his [256], unsigned char *buf, int size){
	int i;

	for (i = 0; i < 256; ++i) {
		his[i] = 0;;
	}

	for (i = 0; i < size; ++i) {
		his[buf[i]]++;
	}
}

void copy (int src[256], int dst[256]){
	int i;
	for (i = 0; i < 256; ++i) {
		dst[i]=src[i];
	}
}

void affiche_histo (int his [256]){
	int i;
	for (i = 0; i < 256; ++i) {
		printf("%d %d\n", i, his[i]);
	}
}

void affiche_img (unsigned char *buf, int h, int w){
	int i;
	for (i = 0; i < h; ++i) {
		int j;
		for (j = 0; j < w; ++j) {
			printf("%d ", buf[i*w+j]);
		}
		printf("\n");
	}
}

int diff_int (int a, int b){
	return a>b?a-b:b-a;
}

int max_int(int a, int b){
	return a>b?a:b;
}

int diff (int hist1 [256], int hist2 [256]){
	int i;
	int max=0;
	for (i = 0; i < 256; ++i) {
		max = max_int(max, diff_int(hist1[i], hist2[i]));
	}
	return max;
}
