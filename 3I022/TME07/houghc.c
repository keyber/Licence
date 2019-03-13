#include <inrimage/image.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* retourne 1 si (ix,iy) appartient a la droite
 * d'equation x*cos(theta) + y*sin(theta) = rho
 */ 

int pixelin(int x, int y, float x0, float y0, float r, float tolerance) {
    return fabs((x-x0)*(x-x0) + (y-y0)*(y-y0) - r*r) < tolerance; 
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

int *hough( int *ntheta1, int *ntheta2, int *nrho, 
	    float dtheta, float drho,
	    float tolerance,
	    unsigned char *bufin, int dimx, int dimy) {
    float rmax = sqrt((double)(dimx*dimx+dimy*dimy));
    *nrho = (int)(rmax/drho);
    *ntheta1 = (int)(dimx/dtheta);
    *ntheta2 = (int)(dimy/dtheta);
    
    int *buf = (int*)(i_malloc(*nrho * *ntheta1 * *ntheta2 * sizeof(int)));
    int i, j;
    for(i = 0; i < *nrho * *ntheta1 * *ntheta2; i++)
        buf[i]=0;
        
    int x0, y0, r;
    for (x0 = 0; x0 < *ntheta1; x0++)
      for (y0 = 0; y0 < *ntheta2; y0++)
        for (r = 0; r < *nrho; r++)
            for(i = 0; i < dimx; i++)
                for(j = 0; j < dimy; j++)
                  //valeur non nulle indique contour
                  if(bufin[i+j*dimx] && pixelin(i,j,x0*dtheta,y0*dtheta, r*drho, tolerance))
                     buf[x0**ntheta2**nrho + y0**nrho + r]++;
       
    return buf;
}

/**
 * Affiche les deux intersections de la droit (theta,r) avec
 * le bord de l'image (carré de coordonnée 1,1,dimx,dimy).
 */
void aux(int x, int y, int r){
  printf("##!draw(a %d %d %d)\n",x+1-r,y+1-r, 2*r);
}

int is_max_local(int i, int j, int k, int* acc, int sizex, int sizey, int sizez){
  int i2, j2, k2;
  int val = acc[i+j*sizex];
  for(i2 = i-1; i2 <= i+1; i2++)
    for(j2 = j-1; j2 <= j+1; j2++)
    for(k2 = k-1; k2 <= k+1; k2++)
      if(i2>=0&&i2<sizex&&j2>=0&&j2<sizey&&k2>=0&&k2<sizez//not out of bounds
          && acc[i2+j2*sizex+k2*sizex*sizey]>val)//il peut y avoir 2 max de meme valeur
        return 0;
  return 1;
}

int tab_min(int* tab, int size){
  int i, ind_min=0;
	for(i=0;i<size;i++)
	  if(tab[i]<tab[ind_min])
	    ind_min=i;
	return ind_min;
}
/**
 * Cherche les n maxima locaux dans l'accumulateur et pour chacun
 * affiche les intersections de la droite qu'ils représentent avec
 * les bords de l'image.
 */
void findmax( int *acc, int sizex, int sizey, int sizez, float dt, float dr,
	      int n, int dimx, int dimy) {      
	int i, j, k;
	
	//tableau des index dans acc des n maxima locaux
	int tab[n];
	
	//recherche ind du min de acc
	int ind_min = tab_min(acc, sizex*sizey*sizez);
	
	//ini toutes les cases au min
	for(i=0;i<n;i++)
	  tab[i]=ind_min;
	
	//parcourt tout acc et stocke les n max
	for(i = 0; i < sizex; i++){
	    for(j = 0; j < sizey; j++){
	    for(k = 0; k < sizez; k++){
      //ne regarde que les max locaux
      if(is_max_local(i,j,k, acc,sizex,sizey, sizez)){
      
        //recherche min des valeurs indexees par tab
	      int l;
	      ind_min=0;
	      for(l=0;l<n;l++)
          if(acc[tab[l]]<acc[tab[ind_min]])
            ind_min = l;
        
        //ij prend la place du min de tab
        if(acc[i+j*sizex+k*sizex*sizey]>acc[tab[ind_min]])
          tab[ind_min] = i*sizey*sizez + j*sizez + k;
      }
}
    }
  }
  
  //affichage
	for(i=0;i<n;i++){
	  printf("%d\n", acc[i]);
	  aux(tab[i]/(sizey*sizez)*dt, ((tab[i]/sizez)%sizey)*dr, tab[i]%sizez);	
  }
}

int main( int argc, char **argv) {
  Fort_int lfmt[9];
  struct image *nf;
  char nom[256];
  unsigned char *buf;
  int *acc;
  float tolerance = 0.5;
  float dtheta=0.02, drho=2.0;
  int nb=10;
  
  inr_init( argc, argv, "1.0", "[input][output] options", 
	    "Compute the Hough transform. Options are\n"
	    "  -n %d: nbcicles\n"
	    "  -t %f: tolerance\n"
	    "  -st %f: increment size for distance\n"
	    "  -sr %f: increment size for rayon\n");

  infileopt(nom);

  /* lecture image: c'est une image de contours codée sur 1 octet */
  nf = image_(nom,"e","",lfmt);
  if( BSIZE != 1 || TYPE != FIXE)
    imerror( 6, "Codage non accepté\n");
  buf= (unsigned char*)i_malloc(DIMX*DIMY*sizeof(unsigned char));
  c_lect(nf, NDIMY, buf);
  fermnf_(&nf);
  
  
  /* à compléter: lecture des paramètres de l'algo, question 3 */
  igetopt1( "-t" , "%f", &tolerance);
  igetopt1( "-st", "%f", &dtheta);
  igetopt1( "-sr", "%f", &drho);
  igetopt1( "-n", "%d", &nb);


  int dimtheta1, dimtheta2, dimrho;
  /* calcul de l'accumulateur de Hough */
  acc = hough(&dimtheta1, &dimtheta2, &dimrho, dtheta, drho, tolerance, buf, DIMX,DIMY);
  findmax(acc, dimtheta1, dimtheta2, dimrho, dtheta, drho, nb, DIMX, DIMY);

  /* écriture de l'accumulateur (pour répondre à la question 3) */
/*  outfileopt( nom);
  NDIMX = DIMX = dimtheta;
  NDIMY = DIMY = dimrho;
  NDIMZ = NDIMV = 1;
  BSIZE=sizeof(int);TYPE=FIXE;EXP=0;
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, acc);
  fermnf_(&nf);
*/                
  return 0;
}


