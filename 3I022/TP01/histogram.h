#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_


void histogramme (int his [256], unsigned char *buf, int size);
void affiche_img (unsigned char *buf, int h, int w);
void affiche_histo (int his [256]);
int diff (int hist1 [256], int hist2 [256]);
void copy (int src[256], int dst[256]);


#endif
