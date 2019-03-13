#include <inrimage/image.h>
#include "splitmerge.h"


int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  char nom[128];
  GNode *qt;
  float split_thresh = 100;
  float merge_thresh = 400;
  int count, xmin = 2, ymin = 2;
  int nbits;
  int nb=0;
  
  inr_init ( argc, argv, "1.0", 
	     "[input] [output] [-min xmin ymin] -s seuil -m smerge", 
	     "segmentation par split");

  infileopt( nom);
  nf = image_( nom, "e", "", lfmt);
  if ( TYPE != FIXE || BSIZE != 1)
    imerror( 6, "Codage non acceptable\n");
  buf = i_malloc(DIMX*DIMY);
  c_lect( nf, DIMY, buf);
  fermnf_( &nf);

  igetopt1( "-s", "%f", &split_thresh);
  igetopt1( "-m", "%f", &merge_thresh);
  igetopt2( "-min", "%d", &xmin, "%d", &ymin);
  
  /*PHASE DE DECOUPAGE*/
  qt = split( buf, DIMX, DIMY, split_thresh, xmin, ymin);	
	
	/*PHASE DE FUSION*/
	
	GSList *liste=merge_list_regions(qt);
	printf("nb region avant : %d\n",g_slist_length(liste));
	
	/* Compléter cette partie pour répondre à la question
     1.4 : affichage des statistiques */
  GSList *res = merge( liste, merge_thresh);
	merge_segment( res, buf, DIMX);
	
	printf("nb region apres : %d\n",g_slist_length(res));
	
	outfileopt( nom);
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, buf);
  fermnf_( &nf);
}
