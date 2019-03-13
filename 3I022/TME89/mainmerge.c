#include <inrimage/image.h>
#include "splitmerge.h"


int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  char nom[128];
  GNode *qt;
  float split_thresh = 100, merge_thresh = 200;
  int count, xmin = 2, ymin = 2;
  int nbits;
  
  inr_init ( argc, argv, "1.0", 
	     "[input] [output] [-min xmin ymin] -s seuilS -m seuilM", 
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
  
  fprintf(stderr, "dim, thresh, min : %d %d %f %d %d \n", DIMX, DIMY, split_thresh, xmin, ymin);
  qt = split( buf, DIMX, DIMY, split_thresh, xmin, ymin);
	
	//////MERGE//////
	GSList *liste=merge_list_regions(qt);
	printf("nb regions : %d\n",g_slist_length(liste));
	
	GSList *res = merge( liste, merge_thresh);
	merge_segment( res, buf, DIMX);
	
	printf("nb regions apres : %d\n",g_slist_length(res));
	
	outfileopt( nom);
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, buf);
  fermnf_( &nf);
}
