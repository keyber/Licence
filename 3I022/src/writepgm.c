#include <stdio.h>
#include <stdlib.h>

int writepgm( char *nom, unsigned char *buf, int w, int h) {
  FILE *fp = fopen( nom, "w");
  
  if( fp != NULL) {
    fprintf( fp, "P5\n%d %d\n255\n", w, h);
    fwrite( buf, sizeof(char), w*h, fp);
    fclose( fp);
    return 1;
  }
  fprintf(stderr,"writepgm: write error with %s\n", nom);
  return 0;
}

