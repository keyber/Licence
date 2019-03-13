#include "splitmerge.h"


/* TME8 */
static
region *creer_region( unsigned char *buf, int ix, int iy, int x, int y, int dimx) {
  region *r = (region *) g_malloc( sizeof(region));
  int i,j;
  float v;
  
  r->ix = ix;
  r->iy = iy;
  r->x  = x;
  r->y  = y;

  r -> n = r->x * r->y;
  r -> mu = r-> var = 0;
  
  /* calcul des moyenne et variance de la region*/
  for(j=0; j<r->y; j++)
  	for(i=0; i<r->x; i++)
  		r->mu += buf[i + r->ix-1 + dimx*(j+r->iy-1)];
  r->mu/=r->n;
  
  /* à compléter pour répondre à la question 1.1 */
  for(j=0; j<r->y; j++)
  	for(i=0; i<r->x; i++){
  		v = buf[i + r->ix-1 + dimx*(j+r->iy-1)];
  		r->var += (v-r->mu)*(v-r->mu);
  	}
  	
  r->var /= r->n;
  return r;  
}


static
void split_rec( unsigned char *buf, int dimx, GNode *noeud, float t, int xmin, int ymin) {
  region *r = noeud -> data;
  region *sreg;

  if( r->x/2 >= xmin && r->y/2 >= ymin && 
      r->x % 2 == 0 && r->y % 2 == 0 &&
      predsplit( r, t) ) {
    sreg = creer_region( buf,r->ix,r->iy,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
    sreg = creer_region( buf,r->ix+r->x/2,r->iy,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
    sreg = creer_region( buf,r->ix,r->iy+r->y/2,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
    sreg = creer_region( buf,r->ix+r->x/2,r->iy+r->y/2,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
  }
}


GNode *split( unsigned char *buf, int dimx, int dimy, float threshold,
	      int xmin, int ymin) {
  region *racine;
  GNode *qt;
  racine = creer_region( buf, 1, 1, dimx, dimy, dimx);
  qt = g_node_new(racine);
  split_rec( buf, dimx, qt, threshold, xmin, ymin);
  return qt;
}
