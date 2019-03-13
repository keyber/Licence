#include <inrimage/image.h>
#include "splitmerge.h"


int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  char nom[128];
  GNode *qt;
  float split_thresh = 200;
  int count, xmin = 2, ymin = 2;
  int nbits;
  int nb=0;
  
  inr_init ( argc, argv, "1.0", 
	     "[input] [output] [-min xmin ymin] -s seuil", 
	     "segmentation par split");

  infileopt( nom);
  nf = image_( nom, "e", "", lfmt);
  if ( TYPE != FIXE || BSIZE != 1)
    imerror( 6, "Codage non acceptable\n");
  buf = i_malloc(DIMX*DIMY);
  c_lect( nf, DIMY, buf);
  fermnf_( &nf);

  igetopt1( "-s", "%f", &split_thresh);
  igetopt2( "-min", "%d", &xmin, "%d", &ymin);
  
  qt = split( buf, DIMX, DIMY, split_thresh, xmin, ymin);

  fprintf( stderr, "stats image: %g %g\n",
	   ((region*)qt->data)->mu, ((region*)qt->data)->var);

  /* Pour répondre l'exercice 1.2 */
  //split_print_regions( qt);

  /* Compléter cette partie pour répondre à la question
     1.3: appel à split_segment() et écriture image */
  
	nb = split_segment( qt, buf, DIMX);
	
	fprintf( stderr, "nombre de region detectee : %d\n",nb);
	
	outfileopt( nom);
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, buf);
  fermnf_( &nf);
	
  
  /* Compléter cette partie pour répondre à la question
     1.4 : affichage des statistiques */

}
