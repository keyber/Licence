#include <inrimage/image.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* retourne 1 si (ix,iy) appartient a la droite
 * d'equation x*cos(theta) + y*sin(theta) = rho
 */ 

int pixelinline( int ix, int iy, float theta, float rho, float tolerance) {
    return fabs(ix*cos(theta) + iy*sin(theta) - rho) < tolerance; 
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
    float rmax = sqrt((double)(dimx*dimx+dimy*dimy));
    *nrho = (int)(rmax/drho);
    *ntheta = (int)(3*M_PI_2/dtheta);
    
    int *buf = (int*)(i_malloc(*nrho * *ntheta * sizeof(int)));
    int i, j;
    for(i = 0; i < *nrho * *ntheta; i++)
        buf[i]=0;
        
    //printf("%d  %d  %f  %f  %f  %d  %d\n", *ntheta, *nrho, dtheta, drho, tolerance, dimx, dimy);
                
    int r, t;
    for (r = 0; r < *nrho; r++)
        for (t = 0; t < *ntheta; t++)
            for(i = 0; i < dimy; i++)
                for(j = 0; j < dimx; j++)
                  //valeur non nulle indique contour
                  if(bufin[j+i*dimx] && pixelinline(i,j,t*dtheta-M_PI_2,r*drho,tolerance))
                     buf[r * *ntheta + t]++;
       
    return buf;
}

/**
 * Affiche les deux intersections de la droit (theta,r) avec
 * le bord de l'image (carré de coordonnée 1,1,dimx,dimy).
 */
void auxline(int* debut, int x, int y){
	  if(*debut)
  		printf("##!draw(p %d %d)\n",x+1,y+1);
		else
		  printf("##!draw(l %d %d)\n",x+1,y+1);
		*debut=0;
}

void houghlines(int* bufin, float theta, float r, int dimx, int dimy) {
  int debut=1;
  double c = cos(theta);
  double s = sin(theta);
	int x,y;
	x=1;
	y=(int)((r-c)/s);
	if(1<=y&&y<=dimy)
	  auxline(&debut,x,y);
	
	y=1;
  x=(int)((r-s)/c);
	if(1<=x&&x<=dimx)
	  auxline(&debut,x,y);
	
	x=dimx;
	y=(int)((r-dimx*c)/s);
	if(1<=y&&y<=dimy)
	  auxline(&debut,x,y);
	
	y=dimy;
	x=(int)((r-dimy*s)/c);
  if(1<=x&&x<=dimx)
	  auxline(&debut,x,y);
	  
	if(debut){
	  printf("erreur, pas d'intersection trouvee. Reessayer avec nb de ligne plus faible\n");
	  exit(1);
	  /*
	  printf("%f %f %lf %lf\n", theta, r, c, s);
	  printf("%d %d %d %d\n", (int)((r-c)/s), (int)((r-s)/c), (int)((r-dimx*c)/s), (int)((r-dimy*s)/c));
	  
	  int i,j;
    for(i = 0; i < dimx; i++)
        for(j = 0; j < dimy; j++)
            //valeur non nulle indique contour
            if(bufin[i+j*dimx] && pixelinline(i,j,theta,r,0.5))
              printf("%d %d\n", i, j);
	*/
	}
}

/** i, j : num ligne, colonne*/
int is_max_local(int i, int j, int* acc, int sizex, int sizey){
  int i2, j2;
  int val = acc[i+j*sizex];
  for(i2 = i-1; i2 <= i+1; i2++)
    for(j2 = j-1; j2 <= j+1; j2++)
      if(i2>=0&&i2<sizey&&j2>=0&&j2<sizex//not out of bounds
          && acc[j2+i2*sizex]>val)//il peut y avoir 2 max de meme valeur
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
void findmax( int *acc, int sizex, int sizey, float dt, float dr,
	      int n, int dimx, int dimy) {      
	int i, j;
	
	//tableau des index dans acc des n maxima locaux
	int tab[n];
	
	//recherche ind du min de acc
	int ind_min = tab_min(acc, sizex*sizey);
	
	//ini toutes les cases au min
	for(i=0;i<n;i++)
	  tab[i]=ind_min;
	
	//parcourt tout acc et stocke les n max
	for(i = 0; i < sizey; i++){//pour chaque ligne
    for(j = 0; j < sizex; j++){//pour chaque colonne
      //ne regarde que les max locaux
      if(is_max_local(i,j,acc,sizex,sizey)){
      
        //recherche min des valeurs indexees par tab
	      int k;
	      ind_min=0;
	      for(k=0;k<n;k++)
          if(acc[tab[k]]<acc[tab[ind_min]])
            ind_min = k;
        
        //ij prend la place du min de tab
        if(acc[j+i*sizex]>acc[tab[ind_min]])
          tab[ind_min]=j+i*sizex;
      }
    }
  }
  
  //affichage
	for(i=0;i<n;i++){
	 // printf("\n\n%d %f %d %f %d\n", tab[i]%sizex, tab[i]%sizex*dt-M_PI_2,
	   //                              tab[i]/sizex, tab[i]/sizex*dr, acc[tab[i]]);
	  houghlines(acc, tab[i]/sizex*dt-M_PI_2, tab[i]%sizex*dr, dimx, dimy);	
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
  int dimtheta, dimrho;
  int nb=10;
  
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
  igetopt1( "-t" , "%f", &tolerance);
  igetopt1( "-st", "%f", &dtheta);
  igetopt1( "-sr", "%f", &drho);
  igetopt1( "-nb", "%d", &nb);


  /* calcul de l'accumulateur de Hough */
  acc = hough(&dimtheta, &dimrho, dtheta, drho, tolerance, buf, DIMX,DIMY);
  findmax(acc, dimtheta, dimrho, dtheta, drho, nb, DIMX, DIMY);

  /* écriture de l'accumulateur (pour répondre à la question 3) */
  outfileopt( nom);
  NDIMX = DIMX = dimtheta/* à compléter, question 3 */ ;
  NDIMY = DIMY = dimrho/* à compléter, question 3 */;
  NDIMZ = NDIMV = 1;
  /* codage sur 4 octets en virgule fixe */
  BSIZE=sizeof(int);TYPE=FIXE;EXP=0;
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, acc);
  fermnf_(&nf);
                

  /* Décommenter ici l'appel à la fonction findmax()*/
  return 0;
}

