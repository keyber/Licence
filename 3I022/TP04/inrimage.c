/*
  BEROUKHIM Keyvan 3506789
*/

#include <inrimage/image.h>
#include <stdlib.h>
#include <stdio.h>

static char version[]="1.00";
static char usage[]="[input][output][-d cotefiltre]";
static char detail[]="applique filtre median";
  
char valeur (int x, int y, unsigned char *buf){
  if(x<0 || x>=NDIMX || y<0 || y>=NDIMY) return 0;
  return buf[x*NDIMY+y];
}

char moy (int r, int x, int y, unsigned char *buf){
  int s = 0, i, j;
  for(i=x; i<r+x;i++)
    for(j=y;j<r+y;j++)
      s+=valeur(i,j,buf);
  return (char)((double)s/r/r);
}

int main( int argc, char **argv) {
  char fname[256];
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  int cote=0; 

  /* Initialisation */
  inr_init( argc, argv, version, usage, detail);

  /* Lecture des options */
  igetopt1( "-d", "%d", &cote);
  infileopt( fname);
  
  /* Ouverture et lecture des images */
  nf = image_(fname, "e", "", lfmt);

  /* verification du format */
  if( !(TYPE == FIXE && BSIZE==1))
    imerror( 6, "codage non conforme\n");

  /* allocation memoire adequat */
  buf = (unsigned char*)i_malloc(NDIMX * NDIMY*sizeof(unsigned char));

  /* lecture image */
  c_lect(nf, NDIMY, buf);

  /* fermeture image */
  fermnf_(&nf);

  /* traitement */
  unsigned char* bufout = (unsigned char*)i_malloc(NDIMX * NDIMY*sizeof(unsigned char));
  int i, j;
  for(i=0;i<NDIMX;i++)
    for(j=0;j<NDIMY;j++)
      bufout[i*NDIMY+j] = moy(cote, i, j, buf);
  
  /* Ecriture de l'image */
  outfileopt( fname);
  nf = image_(fname, "c", "", lfmt);
  c_ecr( nf, NDIMY, bufout);
  fermnf_( &nf);
  
  i_Free( (void*)&buf);
  i_Free( (void*)&bufout);
  return 0;
}
