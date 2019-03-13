/*
 * Calcul et affichage de maxima locaux dans une image
 */
#include <inrimage/image.h>


/* calcul des max locaux: à vous ! (question 1) */
void seuilloc( float *out, float *in, int dimx, int dimy, float seuil) {

}

int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  float *bufI, *bufO; 
  float seuil = 1;
  char nom[128];

  inr_init( argc, argv, "", "", "");

  infileopt( nom);
  nf = c_image( nom, "e", "", lfmt);
  bufI = (float*)i_malloc( sizeof(float)*DIMX*DIMY);
  c_lecflt( nf, DIMY, bufI);
  fermnf_( &nf);

  bufO = (float*)i_malloc( sizeof(float)*DIMX*DIMY);

  /* traitement */
  igetopt1( "-n", "%f", &seuil);
  seuilloc( bufO, bufI, dimx, dimy, seuil);


  /* sauvegarde, pour répondre à la question 1 */
  outfileopt( nom);
  TYPE = PACKEE; BSIZE = -1; EXP=0;
  nf = c_image( nom, "c", "", lfmt);
  c_ecrflt( nf, DIMY, bufO);
  fermnf_( &nf);


  /* affichage des coordonnées des max locaux, pour
     répondre à la question 2: à vous ! */

  

  i_Free( (void*)&bufI);
  i_Free( (void*)&bufO);

  return 0;
}

