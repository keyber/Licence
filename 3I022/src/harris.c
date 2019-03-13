/*
 * Detecteur Harris, fichier à compléter
 * gcc harris.c -o harris -linrimage -lm
 */

#include <inrimage/image.h>
#include <math.h>

/*
 * Convolution 2D. 
 * Important: les bords de l'image ne sont pas traités!
 */
void convol( float *out, float *in, int dimx, int dimy,
	     float *noy, int n, int m) {
  int i,j,x,y;
  double s;
  int n2 = n/2, m2 = m/2;

  for( y=0; y<dimy; y++)
    for( x=0; x<dimx; x++) {
      s = 0.;
      for( j=-m2; j<=m2; j++)
	for( i=-n2; i<=n2; i++)
	  if( x>=i && y>=j && x-i<dimx && y-j<dimy)
	    s += in[(x-i)+dimx*(y-j)] * noy[i+n2+(j+m2)*n];
      *out++ = s;
    }
}

int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  float *bufI, *bufH; 
  float kappa = 0.02, sigma = 1;
  char nom[128];

  inr_init( argc, argv, "", "", "");

  infileopt( nom);
  /* lecture en mode flottant => fonctionne avec tout type d'image */
  nf = c_image( nom, "e", "", lfmt);
  bufI = (float*)i_malloc( sizeof(float)*DIMX*DIMY);
  c_lecflt( nf, DIMY, bufI);
  fermnf_( &nf);

  /* paramètres utiles au futur filtre Harris */
  igetopt1( "-K", "%f", &kappa);
  igetopt1( "-s", "%f", &sigma);
  bufH = (float*)i_malloc( sizeof(float)*DIMX*DIMY);

  /* traitement */


  /* sauvegarde, au format virgule flottante */
  outfileopt( nom);
  TYPE =  REELLE; BSIZE = sizeof(float);
  nf = c_image( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, bufH);
  fermnf_( &nf);

  i_Free( (void*)&bufI);
  i_Free( (void*)&bufH);
}

