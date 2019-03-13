#include <inrimage/image.h>
#include <math.h>
#include <stdlib.h>

/* retourne 1 si (ix,iy) appartient a la droite
 * d'equation x*cos(theta) + y*sin(theta) = rho
 */ 

int pixelinline( int ix, int iy, float theta, float rho, float tolerance) {
  /* à compléter, question 1 */
}

/**
 * Transformee de Hough (pour les droites): la fonction calcule le nombre
 * d'intersections entre l'image et la droite d'equation 
 *      x.cos(theta) + y.sin(theta) = rho
 * avec x=0...dimx-1 et y=0...dimy-1
 *      et theta=-PI/2..PI et rho=0...rhomax
 *      rhomax est la longueur de la diagonale de l'image
 *
 * @param buf, dimx, dimy: tampon d'entree et sa taille. Les valeurs au 
 *        dessus d'un seuil sont considerees comme des points de contour
 * @param dtheta, drho : pas de variation de theta et rho
 * @param tolerance tolerance pour le test d'appartenance a la droite
 * @param ntheta,nrho: nombre de colonnes et de lignes pour le tampon 
 *         d'accumulation retournee par la fonction. 
 *         nrho depend de la taille de l'image et du pas drho, ntheta 
 *         ne depend que du pas dtheta.
 * @return le tampon de l'accumulateur de hough, alloue par la fonction.
 */

int *hough( int *ntheta, int *nrho, 
	    float dtheta, float drho,
	    float tolerance,
	    unsigned char *bufin, int dimx, int dimy) {
  /* à compléter, question 2 */

}

/**
 * Affiche les deux intersections de la droit (theta,r) avec
 * le bord de l'image (carré de coordonnée 1,1,dimx,dimy).
 */

void houghlines( float theta, float r, int dimx, int dimx) {
  /* à compléter, question 4 */
}

/**
 * Cherche les n maxima locaux dans l'accumulateur et pour chacun
 * affiche les intersections de la droite qu'ils représentent avec
 * les bords de l'image.
 */
void findmax( int *acc, int sizex, int sizey, double dr, double dt,
	      int n, int dimx, int dimy) {
  /* à compléter, question 5 */
}

int main( int argc, char **argv) {
  Fort_int lfmt[9];
  struct image *nf;
  char nom[256];
  unsigned char *buf;
  int *acc;
  float tolerance = 0.5;
  float dtheta, drho=1;
  int dimtheta, dimrho;

  inr_init( argc, argv, "1.0", "[input][output] options", 
	    "Compute the Hough transform. Options are\n"
	    "  -t %f: tolerance\n"
	    "  -st %f: increment size for angle\n"
	    "  -sr %f: increment size for distance\n");

  infileopt(nom);

  /* lecture image: c'est une image de contours codée sur 1 octet */
  nf = image_(nom,"e","",lfmt);
  if( BSIZE != 1 || TYPE != FIXE)
    imerror( 6, "Codage non accepté\n");
  buf= (unsigned char*)i_malloc(DIMX*DIMY*sizeof(unsigned char));
  c_lect(nf, NDIMY, buf);
  fermnf_(&nf);
  

  /* à compléter: lecture des paramètres de l'algo, question 3 */


  /* calcul de l'accumulateur de Hough */
  acc = hough( &dimtheta, &dimrho, dtheta, drho, tolerance, buf, DIMX,DIMY);


  /* écriture de l'accumulateur (pour répondre à la question 3) */
  outfileopt( nom);
  NDIMX = DIMX = /* à compléter, question 3 */ ;
  NDIMY = DIMY = /* à compléter, question 3 */;
  NDIMZ = NDIMV = 1;
  /* codage sur 4 octets en virgule fixe */
  BSIZE=sizeof(int);TYPE=FIXE;EXP=0;
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, acc);
  fermnf_(&nf);


  /* Décommenter ici l'appel à la fonction findmax()
     pour répondre à la question 4
      
     findmax( acc, ??, ??, ??, ??,??, NDIMX, NDIMY)

  */
  return 0;
}
