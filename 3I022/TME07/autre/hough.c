#include <inrimage/image.h>
#include <math.h>
#include <stdlib.h>
#include "linkedlist.h"


int local_maxima(int* in,int dimx, int dimy,int x, int y){
  //return if (x,y) is a local maxima in in
  if(!in){
    fprintf(stderr, "Error in local_maxima(), NULL pointer argument\n");
    return 0;
  }

  if(!(x>=0 && x<dimx) || !(y>=0 && y<dimy) ){
    fprintf(stderr, "Error in local_maxima(), invalid argument value\n");
    return 0;
  }

  int imin, imax, jmin, jmax;
  if(x == 0) imin = 0;
  else imin = x-1;

  if(x==dimx-1) imax = x;
  else  imax = x+1;

  if(y == 0) jmin = 0;
  else jmin = y-1;

  if(y==dimy-1) jmax = y;
  else  jmax = y+1;

  for(int j = jmin; j <= jmax; j++)
    for(int i = imin; i <= imax; i++)
      if(in[i+j*dimx]> in[x+y*dimx]) return 0;
  return 1;
}

/* retourne 1 si (ix,iy) appartient a la droite
* d'equation x*cos(theta) + y*sin(theta) = rho
*/
int pixelinline( int ix, int iy, float theta, float rho, float tolerance) {
	return fabs( ix*cos(theta) + iy*sin(theta) -rho)<= tolerance;
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

int *hough( int *ntheta, int *nrho, float dtheta, float drho, float tolerance, unsigned char *bufin, int dimx, int dimy) {
	if(!ntheta || !nrho || !bufin){
		fprintf(stderr, "Error in hough(): NULL pointer argument.\n");
		return NULL;
	}
	float rhomax = sqrt(dimx*dimx + dimy*dimy);

	*ntheta	=	(int)	((3 * M_PI) / (2 * dtheta));
	*nrho		=	(int)	( rhomax / drho);

	int* acc = (int*) calloc( (*ntheta)*(*nrho), sizeof(int));
	if(!acc){
		fprintf(stderr, "Error in hough(), malloc failure.\n");
		return NULL;
	}

	for(int itheta=0; itheta<*ntheta; itheta++){
		// itheta represents the index of theta in the buffer
		// where theta = (3 * pi * itheta) / (2 * ntheta) - (pi/2)
		for(int irho=0; irho<*nrho; irho++){
			//idem for irho where rho = rhomax  * irho / nrho
			for(int i=0; i<dimx; i++){
				for(int j=0; j<dimy; j++){
					if( bufin[i + j*dimx]>200){
						if( pixelinline( i, j, ((3*M_PI)/(2*(*ntheta)))*itheta-(M_PI/2),	irho*(rhomax/(*nrho)),	tolerance) ){
							acc[itheta + irho * *ntheta]++;
						}
					}
				}
			}
		}
	}
	return acc;
}
/*
int *houghCircle( int *nx, int *ny, int* nr, float dx, float dy, float dr, float tolerance, unsigned char *bufin, int dimx, int dimy) {
	if(!nx || !ny || !nr || !bufin){
		fprintf(stderr, "Error in hough(): NULL pointer argument.\n");
		return NULL;
	}
  float rmax = sqrt(dimx*dimx + dimy*dimy);
	*nx  = (int) (dimx / dx);
	*ny  = (int) (dimy / dy);
  *nr  = (int) (rmax / dr);

	int* acc = (int*) calloc( (*nx)*(*ny)*(*nr), sizeof(int));
	if(!acc){
		fprintf(stderr, "Error in hough(), malloc failure.\n");
		return NULL;
	}

  for(int ix =0; ix < *nx; ix++){
    for(int iy=0; iy < *iy; j+){
      for(int ir = 0; ir < nr; ir++){

      }
    }
  }

}
*/

/**
 * Affiche les deux intersections de la droit (theta,r) avec
 * le bord de l'image (carré de coordonnée 1,1,dimx,dimy).
 */

void houghlines( float theta, float rho, int dimx, int dimy) {
	int Ax, Ay, Bx, By;
	float a, b;
	if(theta < 0){
		a		= rho/cos(theta);
		b		= (dimx - a) / tan(theta);
		Ax	= (int) a;
		Ay	= 1;

		if( b <= dimy){
			Bx = dimx;
			By = b;
		} else {
			Bx = dimx - ( b - dimy) * tan(theta);
			By = dimy;
		}
	} else if ( theta == 0 ){
		Ax = rho;
		Ay = 1;
		Bx = rho;
		By = dimy;
	} else if ( theta < M_PI/2){
		a	= rho/cos(theta);
		b = rho/sin(theta);

		if(a <= dimx){
			Ax = a;
			Ay = 1;
		} else {
			Ax = dimx;
			Ay = b * (a - dimx) / a;
		}

		if(b <= dimy){
			Bx = 1;
			By = b;
		} else {
			Bx = a * (b - dimy) / b;
			By = dimy;
		}
	}
	else if (theta == M_PI/2) {
		Ax = 1;
		Ay = rho;
		Bx = dimx;
		By = rho;
	} else if (theta < M_PI) {
		a = rho / sin(theta);
		b = abs(dimy - a) / tan(theta);

		Ax = 1;
		Ay = a;

		if(b <= dimy){
			Bx = b;
			By = dimy;
		} else {
			Bx = dimx;
			By = dimx - ( (b - dimy) * tan(theta) );
		}
	} else {
		fprintf(stderr, "Error in houghlines(), invalid value for theta\n");
		return;
	}

	printf("##!draw(p %d %d )\n", Ax , Ay );
	printf("##!draw(l %d %d )\n", Bx , By );
}

/**
 * Cherche les n maxima locaux dans l'accumulateur et pour chacun
 * affiche les intersections de la droite qu'ils représentent avec
 * les bords de l'image.
 */
void findmax( int *acc, int sizex, int sizey, double drho, double dtheta, int n, int dimx, int dimy) {
	if(!acc){
		fprintf(stderr, "Error in findmax(): NULL pointer argument.\n");
		return;
	}

	float rhomax = sqrt(dimx*dimx + dimy*dimy);
	int ntheta	=	sizex;	//(int)	((3 * M_PI) / (2 * dtheta));
	int nrho		=	sizey;	//(int)	( rhomax / drho);
	list_value_t* values = NULL;

	for(int itheta=0; itheta<ntheta; itheta++)
		for(int irho=0; irho<nrho; irho++)
			addValue(&values,	acc[itheta + irho *ntheta], itheta, irho );

	list_value_t* current_value = values;
	if(!values) return;
	list_point_t* current_point = values->points;
	while(n && current_value){
		if(local_maxima(acc,ntheta, nrho,current_point->itheta, current_point->irho)){
			float theta = (3 * M_PI * current_point->itheta) / (2 * ntheta) - (M_PI/2);
			float rho = (rhomax  * current_point->irho) / nrho;
			houghlines(theta, rho, dimx, dimy);
			n--;
		}
		current_point = current_point->next;
		if(!current_point){
			current_value = current_value->next;
			if(current_value) current_point = current_value->points;
		}
	}
	freeListValue(values);

}







int main( int argc, char **argv) {
  Fort_int lfmt[9];
  struct image *nf;
  char nom[256];
  unsigned char *buf;
  int *acc;
  float tolerance = 2;
  float dtheta=0.1, drho=1;
  int dimtheta, dimrho, n = 25;

  inr_init( argc, argv, "1.0", "[input][output] options",
	    "Compute the Hough transform. Options are\n"
	    "		-t %f: tolerance\n"
	    "		-st %f: increment size for angle\n"
	    "		-sr %f: increment size for distance\n"
			"		-n %d number of lines\n");

  infileopt(nom);

	 igetopt1( "-t", "%f", &tolerance);
	 igetopt1( "-st", "%f", &dtheta);
	 igetopt1( "-sr", "%f", &drho);
	 igetopt1( "-n", "%d", &n);

  /* lecture image: c'est une image de contours codée sur 1 octet */
  nf = image_(nom,"e","",lfmt);
  if( BSIZE != 1 || TYPE != FIXE) //si l'image n'est pas code sur 1 octet avec virgule fixe
    imerror( 6, "Codage non accepté\n");
  buf= (unsigned char*)i_malloc(DIMX*DIMY*sizeof(unsigned char));
  c_lect(nf, NDIMY, buf);
  fermnf_(&nf);


  /* à compléter: lecture des paramètres de l'algo, question 3 */


  /* calcul de l'accumulateur de Hough */
  acc = hough( &dimtheta, &dimrho, dtheta, drho, tolerance, buf, DIMX,DIMY);
	findmax(acc, dimtheta, dimrho, drho, dtheta, n, DIMX, DIMY);

  /* écriture de l'accumulateur (pour répondre à la question 3) */

  outfileopt( nom);
  NDIMX = DIMX = dimtheta ;
  NDIMY = DIMY = dimrho;
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
	free(acc);
  return 0;
}
