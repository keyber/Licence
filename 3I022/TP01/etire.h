#ifndef ETIRE_H_
#define ETIRE_H_

void etire (int table[], int his[]);
void seuille(unsigned char* src, unsigned char* dst, int size, unsigned char min, unsigned char max);
void applique (unsigned char* src, unsigned char* dst, int size, int table[]);

#endif /* ETIRE_H_ */
