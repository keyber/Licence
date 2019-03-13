/*
 * LI316 - Introduction a l'imagerie numerique
 * Fichier template Inrimage
 */

#include <inrimage/image.h>

static char version[]="1.00";
static char usage[]="[input][output][-sb seuil]";
static char detail[]="";

int main( int argc, char **argv) {
  char fname[256];
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  int sb = 0, i, j;

  /* Initialisation */
  inr_init( argc, argv, version, usage, detail);

  /* Lecture des options */
  igetopt1( "-sb", "%d", &sb);
  infileopt( fname);
  
  /* Ouverture et lecture des images */
  nf = image_(fname, "e", "", lfmt);

  /* verification du format */
  if( !(TYPE == FIXE && BSIZE==1))
    imerror( 6, "codage non conforme\n");

  /* allocation memoire adequat */
  buf = (unsigned char*)i_malloc( NDIMX * NDIMY*sizeof(unsigned char));

  /* lecture image */
  c_lect( nf, NDIMY, buf);

  /* fermeture image */
  fermnf_( &nf);
  
  /* Traitement */
  for( j=0; j<NDIMY; j++)
    for( i=0; i<NDIMX; i++)
      if( buf[i+j*NDIMX] < sb)
	buf[i+j*NDIMX] = 0;

  /* Ecriture de l'image */
  outfileopt( fname);
  nf = image_(fname, "c", "", lfmt);
  c_ecr( nf, NDIMY, buf);
  fermnf_( &nf);
  
  i_Free( (void*)&buf);
  return 0;
}
