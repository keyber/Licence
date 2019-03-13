#include "splitmerge.h"


/* teste si (ix,iy) appartient à la région a */
static gboolean estdans( int ix, int iy, region *a) {
  return ix>=a->ix && iy>=a->iy && ix<a->ix+a->x && iy<a->iy+a->y ;
}

/* return G_TRUE si a et b sont voisins */
static gboolean sontvoisins( region *a, region *b) {
  int x, y;
  
  /* on s'assure que a est plus petit que b */
  if( a->x > b->x && a->y > b->y) {
    region *c=a; 
    a=b; b=c;
  }

  /* test de voisinage */
  x = a->ix + a->x/2;
  y = a->iy + a->y/2;
  return 
    estdans( x+a->x, y, b) ||  // b voisin droit ?
    estdans( x-a->x, y, b) ||  // b voisin gauche ?
    estdans( x, y+a->y, b) ||  // etc
    estdans( x, y-a->y, b) ;
}

/* construit la liste des voisins de r qui sont dans la
 * liste regions */
static GSList *listevoisins( region *r, GSList *regions) {
  GSList *voisins = NULL;

  while( regions) { 
    if( sontvoisins(r,regions->data)) 
      voisins = g_slist_prepend( voisins, regions->data);
    regions = regions->next;
  }
  return voisins;
}

/* Algorithme de fusion tel qu'il a été vu en TD.
 */
GSList *merge( GSList *regions, float threshold) {
  /* apres le traitement, merged contiendra la
   * liste des regions: chaque element
   * sera une liste de regions fusionnees */
  GSList *merged = NULL; 

  while( regions) {
    region *reg = regions->data;
    GSList *voisins;

    merged = g_slist_append( merged, reg);
    regions = g_slist_remove( regions, reg);
    
    /* on cherche les voisins de reg (parmis les
     * regions non fusionnees) */
    voisins = listevoisins( reg, regions);
    reg -> merged = NULL;
    
    /* teste de fusion pour chaque voisin */
    while( voisins) {
      region *vois = voisins->data;

      /* on fusionne vois avec reg ? */
      if( predmerge( reg, vois, threshold)) {
	GSList *voisins2, *r;

	/* vois est retiree de la liste des regions */
	regions = g_slist_remove( regions, vois);
	/* et ajouter la liste des regions fusionnees */
	reg -> merged = g_slist_append( reg->merged, vois);

	/* les voisins de vois sont ajoutes dans la
	   liste de voisins (on verifie s'il n'y a pas de doublon) */
	voisins2 = listevoisins( vois, regions);
	for( r=voisins2; r; r=r->next)
	  if( !g_slist_find( voisins, r->data))
	    voisins = g_slist_append( voisins, r->data);
	g_slist_free( voisins2);
      }
      /* cette region a ete traitee, on la retire des voisins */
      voisins = g_slist_remove( voisins, vois);
    }
  }
  return merged;
}
